//
// ServerSocketImpl.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/ServerSocketImpl.h#1 $
//
// Library: Net
// Package: Sockets
// Module:  ServerSocketImpl
//
// Definition of the ServerSocketImpl class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ServerSocketImpl_INCLUDED
#define Net_ServerSocketImpl_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/SocketImpl.h"


namespace Percipio {
namespace Net {


class Net_API ServerSocketImpl: public SocketImpl
	/// This class implements a TCP server socket.
{
public:
	ServerSocketImpl();
		/// Creates the ServerSocketImpl.

protected:
	virtual ~ServerSocketImpl();
		/// Destroys the ServerSocketImpl.
};


} } // namespace Percipio::Net


#endif // Net_ServerSocketImpl_INCLUDED
