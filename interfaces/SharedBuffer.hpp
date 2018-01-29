/*!************************************************************
 * \file
 * \brief     This file contains the definition of the SharedBuffer class
 * \details   The SharedBuffer class
 * \author    Loïc Touraine <loic.touraine@b-com.com>
 * \if DEBUG
 * \warning   THIS FILE HAS BEEN COMPILATED IN DEBUG MODE
 * \endif
 * \copyright (C) Copyright b<>com\n
 *            This software is the confidential and proprietary
 *            information of b<>com. You shall not disclose such
 *            confidential information and shall use it only in
 *            accordance with the terms of the license agreement
 *            you entered into with b<>com.
 ***************************************************************/

#ifndef __SHAREDBUFFER_HPP__
#define __SHAREDBUFFER_HPP__

#include "SharedFifo.hpp"

template <class T>
class SharedBuffer : public SharedFifo<T>
{
public:
    SharedBuffer(unsigned long max, unsigned long startAt = 0) :
        m_maxSize(max),
        m_bufferedStartOffset( max < startAt ? max : startAt),
        m_started(startAt == 0 ? true : false) {};
    
    ~SharedBuffer() = default;
    
    void push(const T & value) override {
        std::unique_lock<std::mutex> lock(m_mutex);

        while(m_nbNotified >= m_maxSize) {
            m_condQueueNotFull.wait(lock);
        }
        m_data.push_front(value);
        m_nbNotified++;
        
        if (m_started) {
            m_condQueueNotEmpty.notify_one();
        }
        else {
            if (m_nbNotified >= m_bufferedStartOffset) {
                m_started = true;
            }
        }
    }

private:
    unsigned long m_maxSize;
    unsigned long m_bufferedStartOffset;
    bool m_started = false;
    std::condition_variable m_condQueueNotFull;
    using SharedFifo<T>::m_condQueueNotEmpty;
    using SharedFifo<T>::m_nbNotified;
    using SharedFifo<T>::m_data;
    using SharedFifo<T>::m_mutex;

    virtual inline void doPop( T& value ) override
    {
        SharedFifo<T>::doPop(value);
        m_condQueueNotFull.notify_one();
    }
};

#endif
