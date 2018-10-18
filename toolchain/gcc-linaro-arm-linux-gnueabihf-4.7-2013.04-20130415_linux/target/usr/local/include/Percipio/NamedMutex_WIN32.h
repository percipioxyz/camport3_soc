//
// NamedMutex_WIN32.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/NamedMutex_WIN32.h#1 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedMutex
//
// Definition of the NamedMutexImpl class for Windows.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NamedMutex_WIN32_INCLUDED
#define Foundation_NamedMutex_WIN32_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/UnWindows.h"


namespace Percipio {


class Foundation_API NamedMutexImpl
{
protected:
	NamedMutexImpl(const std::string& name);
	~NamedMutexImpl();
	void lockImpl();
	bool tryLockImpl();
	void unlockImpl();
	
private:
	std::string _name;
	HANDLE      _mutex;
};


} // namespace Percipio


#endif // Foundation_NamedMutex_WIN32_INCLUDED
