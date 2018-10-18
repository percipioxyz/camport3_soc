//
// NullPartHandler.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/NullPartHandler.h#1 $
//
// Library: Net
// Package: Messages
// Module:  NullPartHandler
//
// Definition of the NullPartHandler class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_NullPartHandler_INCLUDED
#define Net_NullPartHandler_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/Net/PartHandler.h"


namespace Percipio {
namespace Net {


class Net_API NullPartHandler: public PartHandler
	/// A very special PartHandler that simply discards all data.
{
public:
	NullPartHandler();
		/// Creates the NullPartHandler.
	
	~NullPartHandler();
		/// Destroys the NullPartHandler.
	
	void handlePart(const MessageHeader& header, std::istream& stream);
		/// Reads and discards all data from the stream.
};


} } // namespace Percipio::Net


#endif // Net_NullPartHandler_INCLUDED
