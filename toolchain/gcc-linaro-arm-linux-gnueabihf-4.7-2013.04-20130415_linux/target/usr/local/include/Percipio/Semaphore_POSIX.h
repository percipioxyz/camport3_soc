//
// Semaphore_POSIX.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Semaphore_POSIX.h#1 $
//
// Library: Foundation
// Package: Threading
// Module:  Semaphore
//
// Definition of the SemaphoreImpl class for POSIX Threads.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Semaphore_POSIX_INCLUDED
#define Foundation_Semaphore_POSIX_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include <pthread.h>
#include <errno.h>


namespace Percipio {


class Foundation_API SemaphoreImpl
{
protected:
	SemaphoreImpl(int n, int max);		
	~SemaphoreImpl();
    int  getValueImpl();
    int  getWaitedCountImpl();
    void resetImpl(int n);
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	
private:
	volatile int    _n;
    volatile int    _nWaiter;
	int             _max;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;
};


//
// inlines
//
inline int SemaphoreImpl::getValueImpl()
{
    return _n;
}


inline int SemaphoreImpl::getWaitedCountImpl()
{
    return _nWaiter;
}


inline void SemaphoreImpl::resetImpl(int n)
{
	if (pthread_mutex_lock(&_mutex))	
		throw SystemException("cannot signal semaphore (lock)");
    bool needSignal = (_n == 0);
    _n = n;
	if (needSignal && pthread_cond_signal(&_cond))
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal semaphore");
	}
	pthread_mutex_unlock(&_mutex);
}


inline void SemaphoreImpl::setImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw SystemException("cannot signal semaphore (lock)");
	if (_n < _max)
	{
		++_n;
	}
	else
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal semaphore: count would exceed maximum");
	}	
	if (pthread_cond_signal(&_cond))
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal semaphore");
	}
	pthread_mutex_unlock(&_mutex);
}


} // namespace Percipio


#endif // Foundation_Semaphore_POSIX_INCLUDED
