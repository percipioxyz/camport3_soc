//
// HTTPRequestHandlerFactory.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/HTTPRequestHandlerFactory.h#1 $
//
// Library: Net
// Package: HTTPServer
// Module:  HTTPRequestHandlerFactory
//
// Definition of the HTTPRequestHandlerFactory class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_HTTPRequestHandlerFactory_INCLUDED
#define Net_HTTPRequestHandlerFactory_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/SharedPtr.h"
#include "Percipio/BasicEvent.h"


namespace Percipio {
namespace Net {


class HTTPServerRequest;
class HTTPServerResponse;
class HTTPRequestHandler;


class Net_API HTTPRequestHandlerFactory
	/// A factory for HTTPRequestHandler objects.
	/// Subclasses must override the createRequestHandler()
	/// method.
{
public:
	typedef Percipio::SharedPtr<HTTPRequestHandlerFactory> Ptr;
	
	HTTPRequestHandlerFactory();
		/// Creates the HTTPRequestHandlerFactory.

	virtual ~HTTPRequestHandlerFactory();
		/// Destroys the HTTPRequestHandlerFactory.

	virtual HTTPRequestHandler* createRequestHandler(const HTTPServerRequest& request) = 0;
		/// Must be overridden by sublasses.
		///
		/// Creates a new request handler for the given HTTP request.

protected:
	Percipio::BasicEvent<const bool> serverStopped;

private:
	HTTPRequestHandlerFactory(const HTTPRequestHandlerFactory&);
	HTTPRequestHandlerFactory& operator = (const HTTPRequestHandlerFactory&);
	
	friend class HTTPServer;
	friend class HTTPServerConnection;
};


} } // namespace Percipio::Net


#endif // Net_HTTPRequestHandlerFactory_INCLUDED
