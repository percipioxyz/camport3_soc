//
// HTTPBasicStreamBuf.h
//
// $Id: //percipio/Main/template/class.h#4 $
//
// Library: Net
// Package: HTTP
// Module:  HTTPBasicStreamBuf
//
// Definition of the HTTPBasicStreamBuf class.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_HTTPBasicStreamBuf_INCLUDED
#define Net_HTTPBasicStreamBuf_INCLUDED


#include "Percipio/Net/Net.h"
#include "Percipio/BufferedStreamBuf.h"
#include "Percipio/Net/HTTPBufferAllocator.h"


namespace Percipio {
namespace Net {


typedef Percipio::BasicBufferedStreamBuf<char, std::char_traits<char>, HTTPBufferAllocator> HTTPBasicStreamBuf;


} } // namespace Percipio::Net


#endif // Net_HTTPBasicStreamBuf_INCLUDED
