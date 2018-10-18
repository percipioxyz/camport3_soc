//
// IPAddressImpl.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/IPAddressImpl.h#2 $
//
// Library: Net
// Package: NetCore
// Module:  IPAddressImpl
//
// Definition of the IPAddressImpl class.
//
// Copyright (c) 2005-2011, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_IPAddressImpl_INCLUDED
#define Net_IPAddressImpl_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/SocketDefs.h"
#ifndef PERCIPIO_HAVE_ALIGNMENT
#include "Percipio/RefCountedObject.h"
#endif
#include <vector>


namespace Percipio {
namespace Net {
namespace Impl {


class IPAddressImpl
#ifndef PERCIPIO_HAVE_ALIGNMENT
	: public Percipio::RefCountedObject
#endif
{
public:
	enum Family
		/// Possible address families for IP addresses.
	{
		IPv4
#ifdef PERCIPIO_HAVE_IPv6
		,IPv6
#endif
	};
	
	virtual ~IPAddressImpl();

	virtual IPAddressImpl* clone() const = 0;
	virtual std::string toString() const = 0;
	virtual percipio_socklen_t length() const = 0;
	virtual const void* addr() const = 0;
	virtual Family family() const = 0;
	virtual int af() const = 0;
	virtual Percipio::UInt32 scope() const = 0;
	virtual bool isWildcard() const	= 0;
	virtual bool isBroadcast() const = 0;
	virtual bool isLoopback() const = 0;
	virtual bool isMulticast() const = 0;
	virtual bool isLinkLocal() const = 0;
	virtual bool isSiteLocal() const = 0;
	virtual bool isIPv4Mapped() const = 0;
	virtual bool isIPv4Compatible() const = 0;
	virtual bool isWellKnownMC() const = 0;
	virtual bool isNodeLocalMC() const = 0;
	virtual bool isLinkLocalMC() const = 0;
	virtual bool isSiteLocalMC() const = 0;
	virtual bool isOrgLocalMC() const = 0;
	virtual bool isGlobalMC() const = 0;
	virtual void mask(const IPAddressImpl* pMask, const IPAddressImpl* pSet) = 0;
	virtual unsigned prefixLength() const = 0;

protected:
	IPAddressImpl();

private:
	IPAddressImpl(const IPAddressImpl&);
	IPAddressImpl& operator = (const IPAddressImpl&);
};


//
// IPv4AddressImpl
//

class IPv4AddressImpl: public IPAddressImpl
{
public:
	IPv4AddressImpl();
	IPv4AddressImpl(const void* addr);
	IPv4AddressImpl(unsigned prefix);
	IPv4AddressImpl(const IPv4AddressImpl& addr);
	IPv4AddressImpl& operator = (const IPv4AddressImpl&);
	std::string toString() const;
	percipio_socklen_t length() const;
	const void* addr() const;
	Family family() const;
	int af() const;
	unsigned prefixLength() const;
	Percipio::UInt32 scope() const;
	bool isWildcard() const;
	bool isBroadcast() const;
	bool isLoopback() const;
	bool isMulticast() const;
	bool isLinkLocal() const;
	bool isSiteLocal() const;
	bool isIPv4Compatible() const;
	bool isIPv4Mapped() const;
	bool isWellKnownMC() const;
	bool isNodeLocalMC() const;
	bool isLinkLocalMC() const;
	bool isSiteLocalMC() const;
	bool isOrgLocalMC() const;
	bool isGlobalMC() const;
	static IPv4AddressImpl parse(const std::string& addr);
	void mask(const IPAddressImpl* pMask, const IPAddressImpl* pSet);
	IPAddressImpl* clone() const;
	IPv4AddressImpl operator & (const IPv4AddressImpl& addr) const;
	IPv4AddressImpl operator | (const IPv4AddressImpl& addr) const;
	IPv4AddressImpl operator ^ (const IPv4AddressImpl& addr) const;
	IPv4AddressImpl operator ~ () const;
	bool operator == (const IPv4AddressImpl& addr) const;
	bool operator != (const IPv4AddressImpl& addr) const;

private:	
	struct in_addr _addr;
};


//
// IPv6AddressImpl
//

class IPv6AddressImpl: public IPAddressImpl
{
public:
	IPv6AddressImpl();
	IPv6AddressImpl(const void* addr);
	IPv6AddressImpl(const void* addr, Percipio::UInt32 scope);
	IPv6AddressImpl(unsigned prefix);
	std::string toString() const;
	percipio_socklen_t length() const;
	const void* addr() const;
	Family family() const;
	int af() const;
	unsigned prefixLength() const;
	Percipio::UInt32 scope() const;
	bool isWildcard() const;
	bool isBroadcast() const;
	bool isLoopback() const;
	bool isMulticast() const;
	bool isLinkLocal() const;
	bool isSiteLocal() const;
	bool isIPv4Compatible() const;
	bool isIPv4Mapped() const;
	bool isWellKnownMC() const;
	bool isNodeLocalMC() const;
	bool isLinkLocalMC() const;
	bool isSiteLocalMC() const;
	bool isOrgLocalMC() const;
	bool isGlobalMC() const;
	static IPv6AddressImpl parse(const std::string& addr);
	void mask(const IPAddressImpl* pMask, const IPAddressImpl* pSet);
	IPAddressImpl* clone() const;
	IPv6AddressImpl operator & (const IPv6AddressImpl& addr) const;
	IPv6AddressImpl operator | (const IPv6AddressImpl& addr) const;
	IPv6AddressImpl operator ^ (const IPv6AddressImpl& addr) const;
	IPv6AddressImpl operator ~ () const;
	bool operator == (const IPv6AddressImpl& addr) const;
	bool operator != (const IPv6AddressImpl& addr) const;
	IPv6AddressImpl(const IPv6AddressImpl& addr);
	IPv6AddressImpl& operator = (const IPv6AddressImpl&);

private:
	struct in6_addr _addr;
	unsigned int    _scope;
};


} } } // namespace Percipio::Net::Impl


#endif // Net_IPAddressImpl_INCLUDED
