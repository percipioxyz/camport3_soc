//
// NetException.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/NetException.h#4 $
//
// Library: Net
// Package: NetCore
// Module:  NetException
//
// Definition of the NetException class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NetException_INCLUDED
#define Net_NetException_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Exception.h"


namespace Percipio {
namespace Net {


PERCIPIO_DECLARE_EXCEPTION(Net_API, NetException, Percipio::IOException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, InvalidAddressException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, InvalidSocketException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, ServiceNotFoundException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, ConnectionAbortedException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, ConnectionResetException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, ConnectionRefusedException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, DNSException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, HostNotFoundException, DNSException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, NoAddressFoundException, DNSException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, InterfaceNotFoundException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, NoMessageException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, MessageException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, MultipartException, MessageException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, HTTPException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, NotAuthenticatedException, HTTPException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, UnsupportedRedirectException, HTTPException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, FTPException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, SMTPException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, POP3Exception, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, ICMPException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, NTPException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, HTMLFormException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, WebSocketException, NetException)
PERCIPIO_DECLARE_EXCEPTION(Net_API, UnsupportedFamilyException, NetException)


} } // namespace Percipio::Net


#endif // Net_NetException_INCLUDED
