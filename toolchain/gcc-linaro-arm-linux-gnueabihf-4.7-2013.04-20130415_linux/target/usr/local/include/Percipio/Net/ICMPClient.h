//
// ICMPClient.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/ICMPClient.h#1 $
//
// Library: Net
// Package: ICMP
// Module:  ICMPClient
//
// Definition of the ICMPClient class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_ICMPClient_INCLUDED
#define Net_ICMPClient_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/ICMPSocket.h"
#include "Percipio/Net/ICMPEventArgs.h"
#include "Percipio/Net/SocketAddress.h"
#include "Percipio/BasicEvent.h"


namespace Percipio {
namespace Net {


class Net_API ICMPClient
	/// This class provides ICMP Ping functionality.
	///
	/// The events are available when class is instantiated
	///	and non-static member functions are called.
	/// 
	///	A "lightweight" alternative is direct (without instantiation)
	///	use of static member functions.
{
public:
	mutable Percipio::BasicEvent<ICMPEventArgs> pingBegin;
	mutable Percipio::BasicEvent<ICMPEventArgs> pingReply;
	mutable Percipio::BasicEvent<ICMPEventArgs> pingError;
	mutable Percipio::BasicEvent<ICMPEventArgs> pingEnd;

	explicit ICMPClient(IPAddress::Family family);
		/// Creates an ICMP client.

	~ICMPClient();
		/// Destroys the ICMP client.

	int ping(SocketAddress& address, int repeat = 1) const;
		/// Pings the specified address [repeat] times.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	int ping(const std::string& address, int repeat = 1) const;
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

	static int ping(SocketAddress& address, IPAddress::Family family, int repeat = 1);
		/// Pings the specified address [repeat] times.
		/// Notifications are not posted for events.
		/// 
		/// Returns the number of valid replies.

	static int pingIPv4(const std::string& address, int repeat = 1);
		/// Calls ICMPClient::ping(SocketAddress&, int) and
		/// returns the result.
		/// 
		/// Returns the number of valid replies.

private:
	mutable IPAddress::Family _family;
};


} } // namespace Percipio::Net


#endif // Net_ICMPClient_INCLUDED
