//
// SocketDefs.h
//
// $Id: //percipio/1.4/Net/include/Percipio/Net/SocketDefs.h#6 $
//
// Library: Net
// Package: NetCore
// Module:  SocketDefs
//
// Include platform-specific header files for sockets.
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Net_SocketDefs_INCLUDED
#define Net_SocketDefs_INCLUDED


#define PERCIPIO_ENOERR 0


#if defined(PERCIPIO_OS_FAMILY_WINDOWS)
	#include "Percipio/UnWindows.h"
	#include <winsock2.h>
	#include <ws2tcpip.h>
	#define PERCIPIO_INVALID_SOCKET  INVALID_SOCKET
	#define percipio_socket_t        SOCKET
	#define percipio_socklen_t       int
	#define percipio_ioctl_request_t int
	#define percipio_closesocket(s)  closesocket(s)
	#define PERCIPIO_EINTR           WSAEINTR
	#define PERCIPIO_EACCES          WSAEACCES
	#define PERCIPIO_EFAULT          WSAEFAULT
	#define PERCIPIO_EINVAL          WSAEINVAL
	#define PERCIPIO_EMFILE          WSAEMFILE
	#define PERCIPIO_EAGAIN          WSAEWOULDBLOCK
	#define PERCIPIO_EWOULDBLOCK     WSAEWOULDBLOCK
	#define PERCIPIO_EINPROGRESS     WSAEINPROGRESS
	#define PERCIPIO_EALREADY        WSAEALREADY
	#define PERCIPIO_ENOTSOCK        WSAENOTSOCK
	#define PERCIPIO_EDESTADDRREQ    WSAEDESTADDRREQ
	#define PERCIPIO_EMSGSIZE        WSAEMSGSIZE
	#define PERCIPIO_EPROTOTYPE      WSAEPROTOTYPE
	#define PERCIPIO_ENOPROTOOPT     WSAENOPROTOOPT
	#define PERCIPIO_EPROTONOSUPPORT WSAEPROTONOSUPPORT
	#define PERCIPIO_ESOCKTNOSUPPORT WSAESOCKTNOSUPPORT
	#define PERCIPIO_ENOTSUP         WSAEOPNOTSUPP
	#define PERCIPIO_EPFNOSUPPORT    WSAEPFNOSUPPORT
	#define PERCIPIO_EAFNOSUPPORT    WSAEAFNOSUPPORT
	#define PERCIPIO_EADDRINUSE      WSAEADDRINUSE
	#define PERCIPIO_EADDRNOTAVAIL   WSAEADDRNOTAVAIL
	#define PERCIPIO_ENETDOWN        WSAENETDOWN
	#define PERCIPIO_ENETUNREACH     WSAENETUNREACH
	#define PERCIPIO_ENETRESET       WSAENETRESET
	#define PERCIPIO_ECONNABORTED    WSAECONNABORTED
	#define PERCIPIO_ECONNRESET      WSAECONNRESET
	#define PERCIPIO_ENOBUFS         WSAENOBUFS
	#define PERCIPIO_EISCONN         WSAEISCONN
	#define PERCIPIO_ENOTCONN        WSAENOTCONN
	#define PERCIPIO_ESHUTDOWN       WSAESHUTDOWN
	#define PERCIPIO_ETIMEDOUT       WSAETIMEDOUT
	#define PERCIPIO_ECONNREFUSED    WSAECONNREFUSED
	#define PERCIPIO_EHOSTDOWN       WSAEHOSTDOWN
	#define PERCIPIO_EHOSTUNREACH    WSAEHOSTUNREACH
	#define PERCIPIO_ESYSNOTREADY    WSASYSNOTREADY
	#define PERCIPIO_ENOTINIT        WSANOTINITIALISED
	#define PERCIPIO_HOST_NOT_FOUND  WSAHOST_NOT_FOUND
	#define PERCIPIO_TRY_AGAIN       WSATRY_AGAIN
	#define PERCIPIO_NO_RECOVERY     WSANO_RECOVERY
	#define PERCIPIO_NO_DATA         WSANO_DATA
	#ifndef ADDRESS_FAMILY
		#define ADDRESS_FAMILY USHORT
	#endif
#elif defined(PERCIPIO_VXWORKS)
	#include <hostLib.h>
	#include <ifLib.h>
	#include <inetLib.h>
	#include <ioLib.h>
	#include <resolvLib.h>
	#include <types.h>
	#include <socket.h>
	#include <netinet/tcp.h>
	#define PERCIPIO_INVALID_SOCKET  -1
	#define percipio_socket_t        int
	#define percipio_socklen_t       int
	#define percipio_ioctl_request_t int
	#define percipio_closesocket(s)  ::close(s)
	#define PERCIPIO_EINTR           EINTR
	#define PERCIPIO_EACCES          EACCES
	#define PERCIPIO_EFAULT          EFAULT
	#define PERCIPIO_EINVAL          EINVAL
	#define PERCIPIO_EMFILE          EMFILE
	#define PERCIPIO_EAGAIN          EAGAIN
	#define PERCIPIO_EWOULDBLOCK     EWOULDBLOCK
	#define PERCIPIO_EINPROGRESS     EINPROGRESS
	#define PERCIPIO_EALREADY        EALREADY
	#define PERCIPIO_ENOTSOCK        ENOTSOCK
	#define PERCIPIO_EDESTADDRREQ    EDESTADDRREQ
	#define PERCIPIO_EMSGSIZE        EMSGSIZE
	#define PERCIPIO_EPROTOTYPE      EPROTOTYPE
	#define PERCIPIO_ENOPROTOOPT     ENOPROTOOPT
	#define PERCIPIO_EPROTONOSUPPORT EPROTONOSUPPORT
	#define PERCIPIO_ESOCKTNOSUPPORT ESOCKTNOSUPPORT
	#define PERCIPIO_ENOTSUP         ENOTSUP
	#define PERCIPIO_EPFNOSUPPORT    EPFNOSUPPORT
	#define PERCIPIO_EAFNOSUPPORT    EAFNOSUPPORT
	#define PERCIPIO_EADDRINUSE      EADDRINUSE
	#define PERCIPIO_EADDRNOTAVAIL   EADDRNOTAVAIL
	#define PERCIPIO_ENETDOWN        ENETDOWN
	#define PERCIPIO_ENETUNREACH     ENETUNREACH
	#define PERCIPIO_ENETRESET       ENETRESET
	#define PERCIPIO_ECONNABORTED    ECONNABORTED
	#define PERCIPIO_ECONNRESET      ECONNRESET
	#define PERCIPIO_ENOBUFS         ENOBUFS
	#define PERCIPIO_EISCONN         EISCONN
	#define PERCIPIO_ENOTCONN        ENOTCONN
	#define PERCIPIO_ESHUTDOWN       ESHUTDOWN
	#define PERCIPIO_ETIMEDOUT       ETIMEDOUT
	#define PERCIPIO_ECONNREFUSED    ECONNREFUSED
	#define PERCIPIO_EHOSTDOWN       EHOSTDOWN
	#define PERCIPIO_EHOSTUNREACH    EHOSTUNREACH
	#define PERCIPIO_ESYSNOTREADY    -4
	#define PERCIPIO_ENOTINIT        -5
	#define PERCIPIO_HOST_NOT_FOUND  HOST_NOT_FOUND
	#define PERCIPIO_TRY_AGAIN       TRY_AGAIN
	#define PERCIPIO_NO_RECOVERY     NO_RECOVERY
	#define PERCIPIO_NO_DATA         NO_DATA
#elif defined(PERCIPIO_OS_FAMILY_UNIX) || defined(PERCIPIO_OS_FAMILY_VMS)
	#include <unistd.h>
	#include <errno.h>
	#include <sys/types.h>
	#include <sys/socket.h>
	#include <fcntl.h>
	#if PERCIPIO_OS != PERCIPIO_OS_HPUX
		#include <sys/select.h>
	#endif
	#include <sys/ioctl.h>
	#if defined(PERCIPIO_OS_FAMILY_VMS)
		#include <inet.h>
	#else
		#include <arpa/inet.h>
	#endif
	#include <netinet/in.h>
	#include <netinet/tcp.h>
	#include <netdb.h>
	#if defined(PERCIPIO_OS_FAMILY_UNIX)
		#if (PERCIPIO_OS == PERCIPIO_OS_LINUX)
			// Net/src/NetworkInterface.cpp changed #include <linux/if.h> to #include <net/if.h>
			// no more conflict, can use #include <net/if.h> here
			#include <net/if.h>
		#elif (PERCIPIO_OS == PERCIPIO_OS_HPUX)
			extern "C"
			{
				#include <net/if.h>
			}
		#else
			#include <net/if.h>
		#endif
	#endif
	#if (PERCIPIO_OS == PERCIPIO_OS_SOLARIS) || (PERCIPIO_OS == PERCIPIO_OS_MAC_OS_X)
		#include <sys/sockio.h>
		#include <sys/filio.h>
	#endif
	#define PERCIPIO_INVALID_SOCKET  -1
	#define percipio_socket_t        int
	#define percipio_socklen_t       socklen_t
	#define percipio_fcntl_request_t int
	#if defined(PERCIPIO_OS_FAMILY_BSD)
		#define percipio_ioctl_request_t unsigned long
	#else
		#define percipio_ioctl_request_t int
	#endif
	#define percipio_closesocket(s)  ::close(s)
	#define PERCIPIO_EINTR           EINTR
	#define PERCIPIO_EACCES          EACCES
	#define PERCIPIO_EFAULT          EFAULT
	#define PERCIPIO_EINVAL          EINVAL
	#define PERCIPIO_EMFILE          EMFILE
	#define PERCIPIO_EAGAIN          EAGAIN
	#define PERCIPIO_EWOULDBLOCK     EWOULDBLOCK
	#define PERCIPIO_EINPROGRESS     EINPROGRESS
	#define PERCIPIO_EALREADY        EALREADY
	#define PERCIPIO_ENOTSOCK        ENOTSOCK
	#define PERCIPIO_EDESTADDRREQ    EDESTADDRREQ
	#define PERCIPIO_EMSGSIZE        EMSGSIZE
	#define PERCIPIO_EPROTOTYPE      EPROTOTYPE
	#define PERCIPIO_ENOPROTOOPT     ENOPROTOOPT
	#define PERCIPIO_EPROTONOSUPPORT EPROTONOSUPPORT
	#if defined(ESOCKTNOSUPPORT)
		#define PERCIPIO_ESOCKTNOSUPPORT ESOCKTNOSUPPORT
	#else
		#define PERCIPIO_ESOCKTNOSUPPORT -1
	#endif
	#define PERCIPIO_ENOTSUP         ENOTSUP
	#define PERCIPIO_EPFNOSUPPORT    EPFNOSUPPORT
	#define PERCIPIO_EAFNOSUPPORT    EAFNOSUPPORT
	#define PERCIPIO_EADDRINUSE      EADDRINUSE
	#define PERCIPIO_EADDRNOTAVAIL   EADDRNOTAVAIL
	#define PERCIPIO_ENETDOWN        ENETDOWN
	#define PERCIPIO_ENETUNREACH     ENETUNREACH
	#define PERCIPIO_ENETRESET       ENETRESET
	#define PERCIPIO_ECONNABORTED    ECONNABORTED
	#define PERCIPIO_ECONNRESET      ECONNRESET
	#define PERCIPIO_ENOBUFS         ENOBUFS
	#define PERCIPIO_EISCONN         EISCONN
	#define PERCIPIO_ENOTCONN        ENOTCONN
	#if defined(ESHUTDOWN)
		#define PERCIPIO_ESHUTDOWN   ESHUTDOWN
	#else
		#define PERCIPIO_ESHUTDOWN   -2
	#endif
	#define PERCIPIO_ETIMEDOUT       ETIMEDOUT
	#define PERCIPIO_ECONNREFUSED    ECONNREFUSED
	#if defined(EHOSTDOWN)
		#define PERCIPIO_EHOSTDOWN   EHOSTDOWN
	#else
		#define PERCIPIO_EHOSTDOWN   -3
	#endif
	#define PERCIPIO_EHOSTUNREACH    EHOSTUNREACH
	#define PERCIPIO_ESYSNOTREADY    -4
	#define PERCIPIO_ENOTINIT        -5
	#define PERCIPIO_HOST_NOT_FOUND  HOST_NOT_FOUND
	#define PERCIPIO_TRY_AGAIN       TRY_AGAIN
	#define PERCIPIO_NO_RECOVERY     NO_RECOVERY
	#define PERCIPIO_NO_DATA         NO_DATA
#endif


#if defined(PERCIPIO_OS_FAMILY_BSD) || (PERCIPIO_OS == PERCIPIO_OS_TRU64) || (PERCIPIO_OS == PERCIPIO_OS_AIX) || (PERCIPIO_OS == PERCIPIO_OS_IRIX) || (PERCIPIO_OS == PERCIPIO_OS_QNX) || (PERCIPIO_OS == PERCIPIO_OS_VXWORKS)
	#define PERCIPIO_HAVE_SALEN 1
#endif


#if PERCIPIO_OS != PERCIPIO_OS_VXWORKS && !defined(PERCIPIO_NET_NO_ADDRINFO)
	#define PERCIPIO_HAVE_ADDRINFO 1
#endif


#if (PERCIPIO_OS == PERCIPIO_OS_HPUX) || (PERCIPIO_OS == PERCIPIO_OS_SOLARIS) || (PERCIPIO_OS == PERCIPIO_OS_WINDOWS_CE) || (PERCIPIO_OS == PERCIPIO_OS_CYGWIN)
	#define PERCIPIO_BROKEN_TIMEOUTS 1
#endif


#if defined(PERCIPIO_HAVE_ADDRINFO)
	#ifndef AI_PASSIVE
		#define AI_PASSIVE 0
	#endif
	#ifndef AI_CANONNAME
		#define AI_CANONNAME 0
	#endif
	#ifndef AI_NUMERICHOST
		#define AI_NUMERICHOST 0
	#endif
	#ifndef AI_NUMERICSERV
		#define AI_NUMERICSERV 0
	#endif
	#ifndef AI_ALL
		#define AI_ALL 0
	#endif
	#ifndef AI_ADDRCONFIG
		#define AI_ADDRCONFIG 0
	#endif
	#ifndef AI_V4MAPPED
		#define AI_V4MAPPED 0
	#endif
#endif


#if defined(PERCIPIO_HAVE_SALEN)
	#define percipio_set_sa_len(pSA, len)  (pSA)->sa_len   = (len)
	#define percipio_set_sin_len(pSA)      (pSA)->sin_len  = sizeof(struct sockaddr_in)
	#if defined(PERCIPIO_HAVE_IPv6)
		#define percipio_set_sin6_len(pSA) (pSA)->sin6_len = sizeof(struct sockaddr_in6)
	#endif
#else
	#define percipio_set_sa_len(pSA, len) (void) 0
	#define percipio_set_sin_len(pSA)     (void) 0
	#define percipio_set_sin6_len(pSA)    (void) 0
#endif


#ifndef INADDR_NONE
	#define INADDR_NONE 0xffffffff
#endif

#ifndef INADDR_ANY
	#define INADDR_ANY 0x00000000
#endif

#ifndef INADDR_BROADCAST
	#define INADDR_BROADCAST 0xffffffff
#endif

#ifndef INADDR_LOOPBACK
	#define INADDR_LOOPBACK 0x7f000001
#endif

#ifndef INADDR_UNSPEC_GROUP
	#define INADDR_UNSPEC_GROUP 0xe0000000
#endif

#ifndef INADDR_ALLHOSTS_GROUP
	#define INADDR_ALLHOSTS_GROUP 0xe0000001
#endif

#ifndef INADDR_ALLRTRS_GROUP
	#define INADDR_ALLRTRS_GROUP 0xe0000002
#endif

#ifndef INADDR_MAX_LOCAL_GROUP
	#define INADDR_MAX_LOCAL_GROUP 0xe00000ff
#endif

#if defined(PERCIPIO_ARCH_BIG_ENDIAN)
	#define percipio_ntoh_16(x) (x)
	#define percipio_ntoh_32(x) (x)
#else
	#define percipio_ntoh_16(x) \
		((((x) >> 8) & 0x00ff) | (((x) << 8) & 0xff00))
	#define percipio_ntoh_32(x) \
		((((x) >> 24) & 0x000000ff) | (((x) >> 8) & 0x0000ff00) | (((x) << 8) & 0x00ff0000) | (((x) << 24) & 0xff000000))
#endif
#define percipio_hton_16(x) percipio_ntoh_16(x)
#define percipio_hton_32(x) percipio_ntoh_32(x)


#if !defined(s6_addr16)
	#if defined(PERCIPIO_OS_FAMILY_WINDOWS)
		#define s6_addr16 u.Word
	#else
		#define s6_addr16 __u6_addr.__u6_addr16
	#endif
#endif


#if !defined(s6_addr32)
	#if defined(PERCIPIO_OS_FAMILY_UNIX)
		#if (PERCIPIO_OS == PERCIPIO_OS_SOLARIS)
			#define s6_addr32 _S6_un._S6_u32
		#else
			#define s6_addr32 __u6_addr.__u6_addr32
		#endif
	#endif
#endif


#endif // Net_SocketDefs_INCLUDED
