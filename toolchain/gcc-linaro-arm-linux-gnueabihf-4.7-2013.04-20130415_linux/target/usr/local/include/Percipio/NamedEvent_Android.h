//
// NamedEvent_Android.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/NamedEvent_Android.h#1 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Definition of the NamedEventImpl class for Android.
//
// Copyright (c) 2004-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NamedEvent_Android_INCLUDED
#define Foundation_NamedEvent_Android_INCLUDED


#include "Percipio/Foundation.h"


namespace Percipio {


class Foundation_API NamedEventImpl
{
protected:
	NamedEventImpl(const std::string& name);	
	~NamedEventImpl();
	void setImpl();
	void waitImpl();
};


} // namespace Percipio


#endif // Foundation_NamedEvent_Android_INCLUDED
