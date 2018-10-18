//
// Environment_VX.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Environment_VX.h#2 $
//
// Library: Foundation
// Package: Core
// Module:  Environment
//
// Definition of the EnvironmentImpl class for VxWorks.
//
// Copyright (c) 2004-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Environment_VX_INCLUDED
#define Foundation_Environment_VX_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Mutex.h"
#include <map>


namespace Percipio {


class Foundation_API EnvironmentImpl
{
public:
	typedef UInt8 NodeId[6]; /// Ethernet address.

	static std::string getImpl(const std::string& name);	
	static bool hasImpl(const std::string& name);	
	static void setImpl(const std::string& name, const std::string& value);
	static std::string osNameImpl();
	static std::string osDisplayNameImpl();
	static std::string osVersionImpl();
	static std::string osArchitectureImpl();
	static std::string nodeNameImpl();
	static void nodeIdImpl(NodeId& id);
	static unsigned processorCountImpl();

private:
	typedef std::map<std::string, std::string> StringMap;
	
	static StringMap _map;
	static FastMutex _mutex;
};


} // namespace Percipio


#endif // Foundation_Environment_VX_INCLUDED
