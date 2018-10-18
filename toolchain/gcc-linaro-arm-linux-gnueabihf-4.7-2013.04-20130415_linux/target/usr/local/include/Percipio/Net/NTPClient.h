//
// NTPClient.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/NTPClient.h#1 $
//
// Library: Net
// Package: NTP
// Module:  NTPClient
//
// Definition of the NTPClient class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NTPClient_INCLUDED
#define Net_NTPClient_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/NTPEventArgs.h"
#include "Percipio/Net/SocketAddress.h"
#include "Percipio/BasicEvent.h"


namespace Percipio {
namespace Net {


class Net_API NTPClient
	/// This class provides NTP (Network Time Protocol) client functionality.
{
public:
	mutable Percipio::BasicEvent<NTPEventArgs> response;

	explicit NTPClient(IPAddress::Family family, int timeout = 3000000);
		/// Creates an NTP client.

	~NTPClient();
		/// Destroys the NTP client.

	int request(SocketAddress& address) const;
		/// Request the time from the server at address.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

	int request(const std::string& address) const;
		/// Request the time from the server at address.
		/// Notifications are posted for events.
		/// 
		/// Returns the number of valid replies.

private:
	mutable IPAddress::Family _family;
	int _timeout;
};


} } // namespace Percipio::Net


#endif // Net_NTPClient_INCLUDED
