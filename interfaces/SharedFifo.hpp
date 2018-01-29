/*!************************************************************
 * \file
 * \brief     This file contains the definition of the SharedFifo class
 * \details   The SharedFifo class
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

#ifndef __SHAREDFIFO_HPP__
#define __SHAREDFIFO_HPP__

#include <deque>
#include <condition_variable>
#include <mutex>

template <class T>
class SharedFifo
{
public:
    SharedFifo() = default;
    ~SharedFifo() = default;
    virtual void push(const T & value) {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_data.push_front(value);
        m_nbNotified++;
        m_condQueueNotEmpty.notify_one();
    }

    const T back() {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_nbNotified == 0) {  // loop to avoid spurious wakeups
            m_condQueueNotEmpty.wait(lock);
        }
        return m_data.back();
    }

    const T pop() {
        std::unique_lock<std::mutex> lock(m_mutex);
        while (m_nbNotified == 0) {  // loop to avoid spurious wakeups
            m_condQueueNotEmpty.wait(lock);
        }
        T value;
        doPop(value);
        return value;
    }

    bool tryPop( T& value )
    {
        std::unique_lock<std::mutex> tryLock(m_mutex, std::defer_lock);
        bool popSuccessful = false;

        if( tryLock.try_lock() )
        {
            if( m_nbNotified > 0)
            {
                doPop(value);
                popSuccessful = true;
            }
        }
        return popSuccessful;
    }

    inline unsigned int size() const {
        return m_data.size();
    }

    inline bool empty() const {
        return m_data.empty();
    }

protected:
    std::condition_variable m_condQueueNotEmpty;
    unsigned long m_nbNotified = 0;
    std::deque<T> m_data;
    std::mutex m_mutex;

    virtual inline void doPop( T& value )
    {
        value = m_data.back();
        m_data.pop_back();
        m_nbNotified--;
    }
};

#endif
