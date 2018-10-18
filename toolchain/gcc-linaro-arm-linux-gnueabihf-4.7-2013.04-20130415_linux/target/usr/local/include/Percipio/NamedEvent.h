//
// NamedEvent.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/NamedEvent.h#2 $
//
// Library: Foundation
// Package: Processes
// Module:  NamedEvent
//
// Definition of the NamedEvent class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_NamedEvent_INCLUDED
#define Foundation_NamedEvent_INCLUDED


#include "Percipio/Foundation.h"


#if defined(PERCIPIO_OS_FAMILY_WINDOWS) && defined(PERCIPIO_WIN32_UTF8)
#include "Percipio/NamedEvent_WIN32U.h"
#elif defined(PERCIPIO_OS_FAMILY_WINDOWS)
#include "Percipio/NamedEvent_WIN32.h"
#elif defined(PERCIPIO_ANDROID)
#include "Percipio/NamedEvent_Android.h"
#elif defined(PERCIPIO_OS_FAMILY_UNIX)
#include "Percipio/NamedEvent_UNIX.h"
#else
#include "Percipio/NamedEvent_VMS.h"
#endif


namespace Percipio {


class Foundation_API NamedEvent: public NamedEventImpl
	/// An NamedEvent is a global synchronization object 
	/// that allows one process or thread to signal an
	/// other process or thread that a certain event
	/// has happened.
	///
	/// Unlike an Event, which itself is the unit of synchronization,
	/// a NamedEvent refers to a named operating system resource being the
	/// unit of synchronization.
	/// In other words, there can be multiple instances of NamedEvent referring
	/// to the same actual synchronization object.
	///
	/// NamedEvents are always autoresetting.
	///
	/// There should not be more than one instance of NamedEvent for
	/// a given name in a process. Otherwise, the instances may
	/// interfere with each other.
{
public:
	NamedEvent(const std::string& name);
		/// Creates the event.
		
	~NamedEvent();
		/// Destroys the event.

	void set();
		/// Signals the event. 
		/// The one thread or process waiting for the event 
		/// can resume execution.

	void wait();
		/// Waits for the event to become signalled.

private:
	NamedEvent();
	NamedEvent(const NamedEvent&);
	NamedEvent& operator = (const NamedEvent&);
};


//
// inlines
//
inline void NamedEvent::set()
{
	setImpl();
}


inline void NamedEvent::wait()
{
	waitImpl();
}


} // namespace Percipio


#endif // Foundation_NamedEvent_INCLUDED
