//
// Event_VX.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Event_VX.h#1 $
//
// Library: Foundation
// Package: Threading
// Module:  Event
//
// Definition of the EventImpl class for VxWorks.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Event_VX_INCLUDED
#define Foundation_Event_VX_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include <semLib.h>


namespace Percipio {


class Foundation_API EventImpl
{
protected:
	EventImpl(bool autoReset);		
	~EventImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	void resetImpl();
	
private:
	bool          _auto;
	volatile bool _state;
	SEM_ID        _sem;
};


} // namespace Percipio


#endif // Foundation_Event_VX_INCLUDED
