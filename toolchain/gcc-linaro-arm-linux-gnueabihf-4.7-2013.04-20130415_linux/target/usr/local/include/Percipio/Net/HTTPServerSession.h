//
// HTTPServerSession.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/HTTPServerSession.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerSession
//
// Definition of the HTTPServerSession class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_HTTPServerSession_INCLUDED
#define Net_HTTPServerSession_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/HTTPSession.h"
#include "Percipio/Net/SocketAddress.h"
#include "Percipio/Net/HTTPServerSession.h"
#include "Percipio/Net/HTTPServerParams.h"
#include "Percipio/Timespan.h"


namespace Percipio {
namespace Net {


class Net_API HTTPServerSession: public HTTPSession
	/// This class handles the server side of a
	/// HTTP session. It is used internally by
	/// HTTPServer.
{
public:
	HTTPServerSession(const StreamSocket& socket, HTTPServerParams::Ptr pParams);
		/// Creates the HTTPServerSession.

	virtual ~HTTPServerSession();
		/// Destroys the HTTPServerSession.
				
	bool hasMoreRequests();
		/// Returns true if there are requests available.
	
	bool canKeepAlive() const;
		/// Returns true if the session can be kept alive.
	
	SocketAddress clientAddress();
		/// Returns the client's address.
		
	SocketAddress serverAddress();
		/// Returns the server's address.
		
private:
	bool           _firstRequest;
	Percipio::Timespan _keepAliveTimeout;
	int            _maxKeepAliveRequests;
};


//
// inlines
//
inline bool HTTPServerSession::canKeepAlive() const
{
	return _maxKeepAliveRequests != 0;
}


} } // namespace Percipio::Net


#endif // Net_HTTPServerSession_INCLUDED
