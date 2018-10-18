//
// DatagramSocketImpl.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/DatagramSocketImpl.h#1 $
//
// Library: Net
// Package: Sockets
// Module:  DatagramSocketImpl
//
// Definition of the DatagramSocketImpl class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_DatagramSocketImpl_INCLUDED
#define Net_DatagramSocketImpl_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/SocketImpl.h"


namespace Percipio {
namespace Net {


class Net_API DatagramSocketImpl: public SocketImpl
	/// This class implements an UDP socket.
{
public:
	DatagramSocketImpl();
		/// Creates an unconnected, unbound datagram socket.

	explicit DatagramSocketImpl(IPAddress::Family family);
		/// Creates an unconnected datagram socket.
		///
		/// The socket will be created for the
		/// given address family.

	DatagramSocketImpl(percipio_socket_t sockfd);
		/// Creates a StreamSocketImpl using the given native socket.
		
protected:
	void init(int af);
	
	~DatagramSocketImpl();
};


} } // namespace Percipio::Net


#endif // Net_DatagramSocketImpl_INCLUDED
