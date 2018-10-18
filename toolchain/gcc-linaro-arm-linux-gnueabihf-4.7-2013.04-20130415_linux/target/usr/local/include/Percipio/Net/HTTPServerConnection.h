//
// HTTPServerConnection.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/HTTPServerConnection.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerConnection
//
// Definition of the HTTPServerConnection class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_HTTPServerConnection_INCLUDED
#define Net_HTTPServerConnection_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/TCPServerConnection.h"
#include "Percipio/Net/HTTPResponse.h"
#include "Percipio/Net/HTTPRequestHandlerFactory.h"
#include "Percipio/Net/HTTPServerParams.h"
#include "Percipio/Mutex.h"


namespace Percipio {
namespace Net {


class HTTPServerSession;


class Net_API HTTPServerConnection: public TCPServerConnection
	/// This subclass of TCPServerConnection handles HTTP
	/// connections.
{
public:
	HTTPServerConnection(const StreamSocket& socket, HTTPServerParams::Ptr pParams, HTTPRequestHandlerFactory::Ptr pFactory);
		/// Creates the HTTPServerConnection.

	virtual ~HTTPServerConnection();
		/// Destroys the HTTPServerConnection.
		
	void run();
		/// Handles all HTTP requests coming in.

protected:
	void sendErrorResponse(HTTPServerSession& session, HTTPResponse::HTTPStatus status);
	void onServerStopped(const bool& abortCurrent);

private:
	HTTPServerParams::Ptr          _pParams;
	HTTPRequestHandlerFactory::Ptr _pFactory;
	bool _stopped;
	Percipio::FastMutex _mutex;
};


} } // namespace Percipio::Net


#endif // Net_HTTPServerConnection_INCLUDED
