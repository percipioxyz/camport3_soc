//
// SharedLibrary_HPUX.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/SharedLibrary_HPUX.h#2 $
//
// Library: Foundation
// Package: SharedLibrary
// Module:  SharedLibrary
//
// Definition of the SharedLibraryImpl class for HP-UX.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_SharedLibrary_HPUX_INCLUDED
#define Foundation_SharedLibrary_HPUX_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Mutex.h"
#include <dl.h>


namespace Percipio {


class Foundation_API SharedLibraryImpl
{
protected:
	SharedLibraryImpl();
	~SharedLibraryImpl();
	void loadImpl(const std::string& path, int flags);
	void unloadImpl();
	bool isLoadedImpl() const;
	void* findSymbolImpl(const std::string& name);
	const std::string& getPathImpl() const;
	static std::string suffixImpl();

private:
	std::string _path;
	shl_t _handle;
	static FastMutex _mutex;
};


} // namespace Percipio


#endif // Foundation_SharedLibrary_HPUX_INCLUDED
