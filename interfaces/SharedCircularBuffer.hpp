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

#ifndef __SHAREDCIRCULARBUFFER_HPP__
#define __SHAREDCIRCULARBUFFER_HPP__

#include "SharedFifo.hpp"

template <class T>
class SharedCircularBuffer  : public SharedFifo<T>
{
public:
    SharedCircularBuffer( unsigned int size )
        : SharedFifo<T>()
        , m_pushCursor( 0 )
        , m_popCursor( 0 )
    {
        m_data = std::deque<T>( size );
    }

    ~SharedCircularBuffer() = default;

    virtual void push(const T & value)
    {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_data[m_pushCursor] = value;
        increaseCursor( m_pushCursor );
        ++m_nbNotified;

        if( m_nbNotified > m_data.size() )
        {
            increaseCursor(m_popCursor);
            --m_nbNotified;
        }

        m_condQueueNotEmpty.notify_one();
    }

protected:
    using SharedFifo<T>::m_condQueueNotEmpty;
    using SharedFifo<T>::m_nbNotified;
    using SharedFifo<T>::m_data;
    using SharedFifo<T>::m_mutex;

    int m_pushCursor;
    int m_popCursor;

    inline void increaseCursor( int& cursor )
    {
        ++cursor;
        if( cursor == m_data.size() )
        {
            cursor = 0;
        }
    }

    virtual inline void doPop( T& value )
    {
        value = m_data[m_popCursor];
        increaseCursor(m_popCursor);
        --m_nbNotified;
    }
};

#endif //__SHAREDCIRCULARBUFFER_HPP__
