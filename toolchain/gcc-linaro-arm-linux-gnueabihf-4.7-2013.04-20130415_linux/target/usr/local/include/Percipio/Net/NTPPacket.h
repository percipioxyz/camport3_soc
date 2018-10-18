//
// NTPPacket.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/NTPPacket.h#1 $
//
// Library: Net
// Package: NTP
// Module:  NTPPacket
//
// Definition of the NTPPacket class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NTPPacket_INCLUDED
#define Net_NTPPacket_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Net/Net.h"
#include "Percipio/Timestamp.h"

namespace Percipio {
namespace Net {


class Net_API NTPPacket
	/// This class is the NTP packet abstraction. 
{
public:
	NTPPacket();
		/// Creates an NTPPacket.

	NTPPacket(Percipio::UInt8 *packet);
		/// Creates an NTPPacket.
		///
		/// Assumed to have at least 48 bytes.

	~NTPPacket();
		/// Destroys the NTPPacket.

	void packet(Percipio::UInt8 *packet) const;
		/// Returns the NTP packet.
		///
		/// Assumed to have at least 48 bytes.

	void setPacket(Percipio::UInt8 *packet);
		/// Returns the NTP packet.
		///
		/// Assumed to have exactly 48 bytes.

	Percipio::Int8 leapIndicator() const;
		/// Returns the leap indicator.

	Percipio::Int8 version() const;
		/// Returns the version.

	Percipio::Int8 mode() const;
		/// Returns the mode.

	Percipio::Int8 stratum() const;
		/// Returns the stratum.

	Percipio::Int8 pool() const;
		/// Returns the pool.

	Percipio::Int8 precision() const;
		/// Returns the precision

	Percipio::Int32 rootDelay() const;
		/// Returns the root delay

	Percipio::Int32 rootDispersion() const;
		/// Returns the root dispersion

	Percipio::Int32 referenceId() const;
		/// Returns the reference id

	Percipio::Int64 referenceTimestamp() const;
		/// Returns the reference timestamp

	Percipio::Int64 originateTimestamp() const;
		/// Returns the originate timestamp

	Percipio::Int64 receiveTimestamp() const;
		/// Returns the receive timestamp

	Percipio::Int64 transmitTimestamp() const;
		/// Returns the transmit timestamp

	Percipio::Timestamp referenceTime() const;
		/// Returns the reference time

	Percipio::Timestamp originateTime() const;
		/// Returns the originate time

	Percipio::Timestamp receiveTime() const;
		/// Returns the receive time

	Percipio::Timestamp transmitTime() const;
		/// Returns the transmit time
private:
	Percipio::Timestamp convertTime(Percipio::Int64 tm) const;

	Percipio::Int8 _leapIndicator;
	Percipio::Int8 _version;
	Percipio::Int8 _mode;
	Percipio::Int8 _stratum;
	Percipio::Int8 _pool;
	Percipio::Int8 _precision;
	Percipio::Int32 _rootDelay;
	Percipio::Int32 _rootDispersion;
	Percipio::Int32 _referenceId;
	Percipio::Int64 _referenceTimestamp;
	Percipio::Int64 _originateTimestamp;
	Percipio::Int64 _receiveTimestamp;
	Percipio::Int64 _transmitTimestamp;
};


//
// inlines
//
inline Percipio::Int8 NTPPacket::leapIndicator() const
{
	return _leapIndicator;
}


inline Percipio::Int8 NTPPacket::version() const
{
	return _version;
}


inline Percipio::Int8 NTPPacket::mode() const
{
	return _mode;
}


inline Percipio::Int8 NTPPacket::stratum() const
{
	return _stratum;
}


inline Percipio::Int8 NTPPacket::pool() const
{
	return _pool;
}


inline Percipio::Int8 NTPPacket::precision() const
{
	return _precision;
}


inline Percipio::Int32 NTPPacket::rootDelay() const
{
	return _rootDelay;
}


inline Percipio::Int32 NTPPacket::rootDispersion() const
{
	return _rootDispersion;
}


inline Percipio::Int32 NTPPacket::referenceId() const
{
	return _referenceId;
}


inline Percipio::Int64 NTPPacket::referenceTimestamp() const
{
	return _referenceTimestamp;
}


inline Percipio::Int64 NTPPacket::originateTimestamp() const
{
	return _originateTimestamp;
}


inline Percipio::Int64 NTPPacket::receiveTimestamp() const
{
	return _receiveTimestamp;
}


inline Percipio::Int64 NTPPacket::transmitTimestamp() const
{
	return _transmitTimestamp;
}


} } // namespace Percipio::Net


#endif // Net_NTPPacket_INCLUDED
