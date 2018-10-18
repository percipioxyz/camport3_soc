//
// SignalHandler.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/SignalHandler.h#2 $
//
// Library: Foundation
// Package: Threading
// Module:  SignalHandler
//
// Definition of the SignalHandler class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_SignalHandler_INCLUDED
#define Foundation_SignalHandler_INCLUDED


#include "Percipio/Foundation.h"


#if defined(PERCIPIO_OS_FAMILY_UNIX) && !defined(PERCIPIO_VXWORKS)


#include <vector>
#include <setjmp.h>


namespace Percipio {


class Foundation_API SignalHandler
	/// This helper class simplifies the handling of POSIX signals.
	///
	/// The class provides a signal handler (installed with
	/// installHandlers()) that translates certain POSIX
	/// signals (SIGILL, SIGBUS, SIGSEGV, SIGSYS) into 
	/// C++ exceptions.
	///
	/// Internally, a stack of sigjmp_buf structs is maintained for
	/// each thread. The constructor pushes a new sigjmp_buf onto
	/// the current thread's stack. The destructor pops the sigjmp_buf
	/// from the stack.
	///
	/// The percipio_throw_on_signal macro creates an instance of SignalHandler
	/// on the stack, which results in a new sigjmp_buf being created.
	/// The sigjmp_buf is then set-up with sigsetjmp().
	///
	/// The handleSignal() method, which is invoked when a signal arrives,
	/// checks if a sigjmp_buf is available for the current thread.
	/// If so, siglongjmp() is used to jump out of the signal handler.
	///
	/// Typical usage is as follows:
	///
	///     try
	///     {
	///          percipio_throw_on_signal;
	///          ...
	///     }
	///     catch (Percipio::SignalException&)
	///     {
	///         ...
	///     }
	///
	/// The best way to deal with a SignalException is to log as much context
	/// information as possible, to aid in debugging, and then to exit.
	///
	/// The SignalHandler can be disabled globally by compiling PERCIPIO and client
	/// code with the PERCIPIO_NO_SIGNAL_HANDLER macro defined.
{
public:
	SignalHandler();
		/// Creates the SignalHandler.

	~SignalHandler();
		/// Destroys the SignalHandler.

	sigjmp_buf& jumpBuffer();
		/// Returns the top-most sigjmp_buf for the current thread.

	static void throwSignalException(int sig);
		/// Throws a SignalException with a textual description  
		/// of the given signal as argument. 
	
	static void install();
		/// Installs signal handlers for SIGILL, SIGBUS, SIGSEGV
		/// and SIGSYS.

protected:
	static void handleSignal(int sig);
		/// The actual signal handler.

	struct JumpBuffer
		/// sigjmp_buf cannot be used to instantiate a std::vector,
		/// so we provide a wrapper struct.
	{
		sigjmp_buf buf;
	};
	typedef std::vector<JumpBuffer> JumpBufferVec;

	static JumpBufferVec& jumpBufferVec();
		/// Returns the JumpBufferVec for the current thread.

private:
	static JumpBufferVec _jumpBufferVec;
	
	friend class ThreadImpl;
};


#ifndef PERCIPIO_NO_SIGNAL_HANDLER
#define percipio_throw_on_signal \
	Percipio::SignalHandler _percipio_signalHandler; \
	int _percipio_signal = sigsetjmp(_percipio_signalHandler.jumpBuffer(), 1); \
	if (_percipio_signal) _percipio_signalHandler.throwSignalException(_percipio_signal);
#else
#define percipio_throw_on_signal
#endif


} // namespace Percipio


#endif // PERCIPIO_OS_FAMILY_UNIX


#endif // Foundation_SignalHandler_INCLUDED
