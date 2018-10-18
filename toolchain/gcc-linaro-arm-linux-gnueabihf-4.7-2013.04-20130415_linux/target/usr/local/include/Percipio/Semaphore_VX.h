//
// Semaphore_VX.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Semaphore_VX.h#1 $
//
// Library: Foundation
// Package: Threading
// Module:  Semaphore
//
// Definition of the SemaphoreImpl class for VxWorks.
//
// Copyright (c) 2004-20011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Semaphore_VX_INCLUDED
#define Foundation_Semaphore_VX_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include "Percipio/AtomicCounter.h"
#include <semLib.h>


namespace Percipio {


class Foundation_API SemaphoreImpl
{
protected:
	SemaphoreImpl(int n, int max);		
	~SemaphoreImpl();
    int  getValueImpl();
    void resetImpl(int n);
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	
private:
	SEM_ID        _sem;
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
	if (semGive(_sem) != OK)
		throw SystemException("cannot signal semaphore");
    _n++;
}


} // namespace Percipio


#endif // Foundation_Semaphore_VX_INCLUDED
