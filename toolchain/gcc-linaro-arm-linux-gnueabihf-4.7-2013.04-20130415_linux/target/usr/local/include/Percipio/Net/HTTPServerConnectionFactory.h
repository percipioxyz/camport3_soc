//
// HTTPServerConnectionFactory.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/HTTPServerConnectionFactory.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPServerConnectionFactory
//
// Definition of the HTTPServerConnectionFactory class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_HTTPServerConnectionFactory_INCLUDED
#define Net_HTTPServerConnectionFactory_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/TCPServerConnectionFactory.h"
#include "Percipio/Net/HTTPRequestHandlerFactory.h"
#include "Percipio/Net/HTTPServerParams.h"


namespace Percipio {
namespace Net {


class Net_API HTTPServerConnectionFactory: public TCPServerConnectionFactory
	/// This implementation of a TCPServerConnectionFactory
	/// is used by HTTPServer to create HTTPServerConnection objects.
{
public:
	HTTPServerConnectionFactory(HTTPServerParams::Ptr pParams, HTTPRequestHandlerFactory::Ptr pFactory);
		/// Creates the HTTPServerConnectionFactory.

	~HTTPServerConnectionFactory();
		/// Destroys the HTTPServerConnectionFactory.

	TCPServerConnection* createConnection(const StreamSocket& socket);
		/// Creates an instance of HTTPServerConnection
		/// using the given StreamSocket.
	
private:
	HTTPServerParams::Ptr          _pParams;
	HTTPRequestHandlerFactory::Ptr _pFactory;
};


} } // namespace Percipio::Net


#endif // Net_HTTPServerConnectionFactory_INCLUDED
