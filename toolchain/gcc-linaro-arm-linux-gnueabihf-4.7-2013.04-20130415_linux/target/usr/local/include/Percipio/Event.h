//
// Event.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Event.h#2 $
//
// Library: Foundation
// Package: Threading
// Module:  Event
//
// Definition of the Event class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Event_INCLUDED
#define Foundation_Event_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Exception.h"
#include "Percipio/AtomicCounter.h"


#if defined(PERCIPIO_OS_FAMILY_WINDOWS)
#include "Percipio/Event_WIN32.h"
#elif defined(PERCIPIO_VXWORKS)
#include "Percipio/Event_VX.h"
#else
#include "Percipio/Event_POSIX.h"
#endif


namespace Percipio {


class Foundation_API Event: private EventImpl
	/// An Event is a synchronization object that
	/// allows one thread to signal one or more
	/// other threads that a certain event
	/// has happened.
	/// Usually, one thread signals an event,
	/// while one or more other threads wait
	/// for an event to become signalled.
{
public:
	Event(bool autoReset = true);
		/// Creates the event. If autoReset is true,
		/// the event is automatically reset after
		/// a wait() successfully returns.
		
	~Event();
		/// Destroys the event.
    
    int approxWaitingCount();
        /// Return approx number of waiting threads

	void set();
		/// Signals the event. If autoReset is true,
		/// only one thread waiting for the event 
		/// can resume execution.
		/// If autoReset is false, all waiting threads
		/// can resume execution.

	void wait();
		/// Waits for the event to become signalled.

	void wait(long milliseconds);
		/// Waits for the event to become signalled.
		/// Throws a TimeoutException if the event
		/// does not become signalled within the specified
		/// time interval.

	bool tryWait(long milliseconds);
		/// Waits for the event to become signalled.
		/// Returns true if the event
		/// became signalled within the specified
		/// time interval, false otherwise.

	void reset();
		/// Resets the event to unsignalled state.
	
private:
	Event(const Event&);
	Event& operator = (const Event&);
    AtomicCounter _n;
};


//
// inlines
//
inline int Event::approxWaitingCount()
{
    return _n.value();
}


inline void Event::set()
{
	setImpl();
}


inline void Event::wait()
{
    _n++;
	waitImpl();
    _n--;
}


inline void Event::wait(long milliseconds)
{
    _n++;
    bool r = waitImpl(milliseconds);
    _n--;
	if (!r)
		throw TimeoutException();
}


inline bool Event::tryWait(long milliseconds)
{
    _n++;
    bool r = waitImpl(milliseconds);
    _n--;
	return r;
}


inline void Event::reset()
{
	resetImpl();
}


} // namespace Percipio


#endif // Foundation_Event_INCLUDED
