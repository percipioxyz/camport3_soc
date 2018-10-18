//
// Semaphore_WIN32.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Semaphore_WIN32.h#1 $
//
// Library: Foundation
// Package: Threading
// Module:  Semaphore
//
// Definition of the SemaphoreImpl class for WIN32.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Semaphore_WIN32_INCLUDED
#define Foundation_Semaphore_WIN32_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include "Percipio/UnWindows.h"
#include "Percipio/AtomicCounter.h"


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
	HANDLE        _sema;
    AtomicCounter _n;
    AtomicCounter _nWaiter;
};


//
// inlines
//
inline int SemaphoreImpl::getValueImpl()
{
    return _n.value();
}


inline int SemaphoreImpl::getWaitedCountImpl()
{
    return _nWaiter.value();
}


inline void SemaphoreImpl::resetImpl(int n)
{
	throw SystemException("cannot reset semaphore");
}


inline void SemaphoreImpl::setImpl()
{
	if (!ReleaseSemaphore(_sema, 1, NULL))
	{
		throw SystemException("cannot signal semaphore");
	}
    _n++;
}


} // namespace Percipio


#endif // Foundation_Semaphore_WIN32_INCLUDED
