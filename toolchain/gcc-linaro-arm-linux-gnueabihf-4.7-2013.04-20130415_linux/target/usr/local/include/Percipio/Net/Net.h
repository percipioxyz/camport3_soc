//
// Net.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/Net.h#2 $
//
// Library: Net
// Package: NetCore
// Module:  Net
//
// Basic definitions for the Percipio Net library.
// This file must be the first file included by every other Net
// header file.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_Net_INCLUDED
#define Net_Net_INCLUDED


#include "Percipio/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the Net_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// Net_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(PERCIPIO_DLL)
	#if defined(Net_EXPORTS)
		#define Net_API __declspec(dllexport)
	#else
		#define Net_API __declspec(dllimport)
	#endif
#endif


#if !defined(Net_API)
	#if !defined(PERCIPIO_NO_GCC_API_ATTRIBUTE) && defined (__GNUC__) && (__GNUC__ >= 4)
		#define Net_API __attribute__ ((visibility ("default")))
	#else
		#define Net_API
	#endif
#endif


//
// Automatically link Net library.
//
#if defined(_MSC_VER)
	#if !defined(PERCIPIO_NO_AUTOMATIC_LIBS) && !defined(Net_EXPORTS)
		#pragma comment(lib, "PercipioNet" PERCIPIO_LIB_SUFFIX)
	#endif
#endif


// Default to enabled IPv6 support if not explicitly disabled
#if !defined(PERCIPIO_NET_NO_IPv6) && !defined (PERCIPIO_HAVE_IPv6)
	#define PERCIPIO_HAVE_IPv6
#elif defined(PERCIPIO_NET_NO_IPv6) && defined (PERCIPIO_HAVE_IPv6)
	#undef PERCIPIO_HAVE_IPv6
#endif // PERCIPIO_NET_NO_IPv6, PERCIPIO_HAVE_IPv6


namespace Percipio {
namespace Net {


void Net_API initializeNetwork();
	/// Initialize the network subsystem.
	/// (Windows only, no-op elsewhere)


void Net_API uninitializeNetwork();
	/// Uninitialize the network subsystem.
	/// (Windows only, no-op elsewhere)


}} // namespace Percipio::Net


//
// Automate network initialization (only relevant on Windows).
//

#if defined(PERCIPIO_OS_FAMILY_WINDOWS) && !defined(PERCIPIO_NO_AUTOMATIC_LIB_INIT) && !defined(__GNUC__)

extern "C" const struct Net_API NetworkInitializer percipioNetworkInitializer;

#if defined(Net_EXPORTS)
	#if defined(_WIN64) || defined(_WIN32_WCE)
		#define PERCIPIO_NET_FORCE_SYMBOL(s) __pragma(comment (linker, "/export:"#s))
	#elif defined(_WIN32)
		#define PERCIPIO_NET_FORCE_SYMBOL(s) __pragma(comment (linker, "/export:_"#s))
	#endif
#else  // !Net_EXPORTS
	#if defined(_WIN64) || defined(_WIN32_WCE)
		#define PERCIPIO_NET_FORCE_SYMBOL(s) __pragma(comment (linker, "/include:"#s))
	#elif defined(_WIN32)
		#define PERCIPIO_NET_FORCE_SYMBOL(s) __pragma(comment (linker, "/include:_"#s))
	#endif
#endif // Net_EXPORTS

PERCIPIO_NET_FORCE_SYMBOL(percipioNetworkInitializer)

#endif // PERCIPIO_OS_FAMILY_WINDOWS


//
// Define PERCIPIO_NET_HAS_INTERFACE for platforms that have network interface detection implemented.
//
#if defined(PERCIPIO_OS_FAMILY_WINDOWS) || (PERCIPIO_OS == PERCIPIO_OS_LINUX) || defined(PERCIPIO_OS_FAMILY_BSD) || (PERCIPIO_OS == PERCIPIO_OS_SOLARIS) || (PERCIPIO_OS == PERCIPIO_OS_QNX)
	#define PERCIPIO_NET_HAS_INTERFACE
#endif


#endif // Net_Net_INCLUDED
