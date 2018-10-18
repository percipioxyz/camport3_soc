//
// SocketNotifier.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/SocketNotifier.h#1 $
//
// Library: Net
// Package: Reactor
// Module:  SocketNotifier
//
// Definition of the SocketNotifier class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SocketNotifier_INCLUDED
#define Net_SocketNotifier_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/Socket.h"
#include "Percipio/RefCountedObject.h"
#include "Percipio/NotificationCenter.h"
#include "Percipio/Observer.h"
#include <set>


namespace Percipio {
namespace Net {


class Socket;
class SocketReactor;
class SocketNotification;


class Net_API SocketNotifier: public Percipio::RefCountedObject
	/// This class is used internally by SocketReactor
	/// to notify registered event handlers of socket events.
{
public:
	explicit SocketNotifier(const Socket& socket);
		/// Creates the SocketNotifier for the given socket.
		
	void addObserver(SocketReactor* pReactor, const Percipio::AbstractObserver& observer);
		/// Adds the given observer. 
		
	void removeObserver(SocketReactor* pReactor, const Percipio::AbstractObserver& observer);
		/// Removes the given observer. 
		
	bool hasObserver(const Percipio::AbstractObserver& observer) const;
		/// Returns true if the given observer is registered.
		
	bool accepts(SocketNotification* pNotification);
		/// Returns true if there is at least one observer for the given notification.
		
	void dispatch(SocketNotification* pNotification);
		/// Dispatches the notification to all observers.
		
	bool hasObservers() const;
		/// Returns true if there are subscribers.
		
	std::size_t countObservers() const;
		/// Returns the number of subscribers;

protected:
	~SocketNotifier();
		/// Destroys the SocketNotifier.

private:
	typedef std::multiset<SocketNotification*> EventSet;

	EventSet                 _events;
	Percipio::NotificationCenter _nc;
	Socket                   _socket;
};


//
// inlines
//
inline bool SocketNotifier::accepts(SocketNotification* pNotification)
{
	return _events.find(pNotification) != _events.end();
}


inline bool SocketNotifier::hasObserver(const Percipio::AbstractObserver& observer) const
{
	return _nc.hasObserver(observer);
}


inline bool SocketNotifier::hasObservers() const
{
	return _nc.hasObservers();
}


inline std::size_t SocketNotifier::countObservers() const
{
	return _nc.countObservers();
}


} } // namespace Percipio::Net


#endif // Net_SocketNotifier_INCLUDED
