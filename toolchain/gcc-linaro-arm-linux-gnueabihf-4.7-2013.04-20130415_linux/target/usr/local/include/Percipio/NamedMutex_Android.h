//
// NamedMutex_Android.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/NamedMutex_Android.h#1 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedMutex
//
// Definition of the NamedMutexImpl class for Android.
//
// Copyright (c) 2004-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NamedMutex_Android_INCLUDED
#define Foundation_NamedMutex_Android_INCLUDED


#include "Percipio/Foundation.h"


namespace Percipio {


class Foundation_API NamedMutexImpl
{
protected:
	NamedMutexImpl(const std::string& name);
	~NamedMutexImpl();
	void lockImpl();
	bool tryLockImpl();
	void unlockImpl();
};


} // namespace Percipio


#endif // Foundation_NamedMutex_Android_INCLUDED
