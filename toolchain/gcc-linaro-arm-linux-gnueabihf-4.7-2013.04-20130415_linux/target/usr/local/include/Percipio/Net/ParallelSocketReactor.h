//
// ParallelSocketReactor.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/ParallelSocketReactor.h#1 $
//
// Library: Net
// Package: Reactor
// Module:  ParallelSocketReactor
//
// Definition of the ParallelSocketReactor class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ParallelSocketReactor_INCLUDED
#define Net_ParallelSocketReactor_INCLUDED


#include "Percipio/Net/SocketReactor.h"
#include "Percipio/Net/SocketNotification.h"
#include "Percipio/Net/StreamSocket.h"
#include "Percipio/Net/ServerSocket.h"
#include "Percipio/NObserver.h"
#include "Percipio/Thread.h"
#include "Percipio/SharedPtr.h"


using Percipio::Net::Socket;
using Percipio::Net::SocketReactor;
using Percipio::Net::ReadableNotification;
using Percipio::Net::ShutdownNotification;
using Percipio::Net::ServerSocket;
using Percipio::Net::StreamSocket;
using Percipio::NObserver;
using Percipio::AutoPtr;
using Percipio::Thread;


namespace Percipio {
namespace Net {


template <class SR>
class ParallelSocketReactor: public SR
{
public:
	typedef Percipio::SharedPtr<ParallelSocketReactor> Ptr;

	ParallelSocketReactor()
	{
		_thread.start(*this);
	}
	
	ParallelSocketReactor(const Percipio::Timespan& timeout):
		SR(timeout)
	{
		_thread.start(*this);
	}
	
	~ParallelSocketReactor()
	{
		try
		{
			this->stop();
			_thread.join();
		}
		catch (...)
		{
			percipio_unexpected();
		}
	}
	
protected:
	void onIdle()
	{
		SR::onIdle();
		Percipio::Thread::yield();
	}
	
private:
	Percipio::Thread _thread;
};


} } // namespace Percipio::Net


#endif // Net_ParallelSocketReactor_INCLUDED
