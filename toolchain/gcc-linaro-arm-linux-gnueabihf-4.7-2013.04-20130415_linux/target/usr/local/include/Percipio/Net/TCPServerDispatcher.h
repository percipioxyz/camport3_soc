//
// TCPServerDispatcher.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/TCPServerDispatcher.h#1 $
//
// Library: Net
// Package: TCPServer
// Module:  TCPServerDispatcher
//
// Definition of the TCPServerDispatcher class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_TCPServerDispatcher_INCLUDED
#define Net_TCPServerDispatcher_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/StreamSocket.h"
#include "Percipio/Net/TCPServerConnectionFactory.h"
#include "Percipio/Net/TCPServerParams.h"
#include "Percipio/Runnable.h"
#include "Percipio/NotificationQueue.h"
#include "Percipio/ThreadPool.h"
#include "Percipio/Mutex.h"


namespace Percipio {
namespace Net {


class Net_API TCPServerDispatcher: public Percipio::Runnable
	/// A helper class for TCPServer that dispatches
	/// connections to server connection threads.
{
public:
	TCPServerDispatcher(TCPServerConnectionFactory::Ptr pFactory, Percipio::ThreadPool& threadPool, TCPServerParams::Ptr pParams);
		/// Creates the TCPServerDispatcher.
		///
		/// The dispatcher takes ownership of the TCPServerParams object.
		/// If no TCPServerParams object is supplied, the TCPServerDispatcher
		/// creates one.

	void duplicate();
		/// Increments the object's reference count.

	void release();
		/// Decrements the object's reference count
		/// and deletes the object if the count
		/// reaches zero.	

	void run();
		/// Runs the dispatcher.
		
	void enqueue(const StreamSocket& socket);
		/// Queues the given socket connection.

	void stop();
		/// Stops the dispatcher.
			
	int currentThreads() const;
		/// Returns the number of currently used threads.

	int maxThreads() const;
		/// Returns the maximum number of threads available.
		
	int totalConnections() const;
		/// Returns the total number of handled connections.
		
	int currentConnections() const;
		/// Returns the number of currently handled connections.	

	int maxConcurrentConnections() const;
		/// Returns the maximum number of concurrently handled connections.	
		
	int queuedConnections() const;
		/// Returns the number of queued connections.	
	
	int refusedConnections() const;
		/// Returns the number of refused connections.

	const TCPServerParams& params() const;
		/// Returns a const reference to the TCPServerParam object.

protected:
	~TCPServerDispatcher();
		/// Destroys the TCPServerDispatcher.

	void beginConnection();
		/// Updates the performance counters.
		
	void endConnection();
		/// Updates the performance counters.

private:
	TCPServerDispatcher();
	TCPServerDispatcher(const TCPServerDispatcher&);
	TCPServerDispatcher& operator = (const TCPServerDispatcher&);

	int _rc;
	TCPServerParams::Ptr _pParams;
	int  _currentThreads;
	int  _totalConnections;
	int  _currentConnections;
	int  _maxConcurrentConnections;
	int  _refusedConnections;
	bool _stopped;
	Percipio::NotificationQueue         _queue;
	TCPServerConnectionFactory::Ptr _pConnectionFactory;
	Percipio::ThreadPool&               _threadPool;
	mutable Percipio::FastMutex         _mutex;
};


//
// inlines
//
inline const TCPServerParams& TCPServerDispatcher::params() const
{
	return *_pParams;
}


} } // namespace Percipio::Net


#endif // Net_TCPServerDispatcher_INCLUDED
