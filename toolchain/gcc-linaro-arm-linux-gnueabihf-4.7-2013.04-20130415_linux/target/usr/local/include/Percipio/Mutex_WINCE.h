//
// Mutex_WIN32.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Mutex_WINCE.h#1 $
//
// Library: Foundation
// Package: Threading
// Module:  Mutex
//
// Definition of the MutexImpl and FastMutexImpl classes for WIN32.
//
// Copyright (c) 2004-2010, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Mutex_WINCE_INCLUDED
#define Foundation_Mutex_WINCE_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include "Percipio/UnWindows.h"


namespace Percipio {


class Foundation_API MutexImpl
{
protected:
	MutexImpl();
	~MutexImpl();
	void lockImpl();
	bool tryLockImpl();
	bool tryLockImpl(long milliseconds);
	void unlockImpl();
	
private:
	HANDLE _mutex;
};


typedef MutexImpl FastMutexImpl;


} // namespace Percipio


#endif // Foundation_Mutex_WINCE_INCLUDED
