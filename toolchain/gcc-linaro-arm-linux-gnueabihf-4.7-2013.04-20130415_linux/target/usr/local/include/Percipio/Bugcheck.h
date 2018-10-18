//
// Bugcheck.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/Bugcheck.h#1 $
//
// Library: Foundation
// Package: Core
// Module:  Bugcheck
//
// Definition of the Bugcheck class and the self-testing macros.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_Bugcheck_INCLUDED
#define Foundation_Bugcheck_INCLUDED


#include "Percipio/Foundation.h"
#include <string>
#if defined(_DEBUG)
#	include <iostream>
#endif


namespace Percipio {


class Foundation_API Bugcheck
	/// This class provides some static methods that are
	/// used by the
	/// percipio_assert_dbg(), percipio_assert(), percipio_check_ptr(), 
	/// percipio_bugcheck() and percipio_unexpected() macros. 
	/// You should not invoke these methods
	/// directly. Use the macros instead, as they
	/// automatically provide useful context information.
{
public:
	static void assertion(const char* cond, const char* file, int line, const char* text = 0);
		/// An assertion failed. Break into the debugger, if
		/// possible, then throw an AssertionViolationException.

	static void nullPointer(const char* ptr, const char* file, int line);
		/// An null pointer was encountered. Break into the debugger, if
		/// possible, then throw an NullPointerException.

	static void bugcheck(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

	static void bugcheck(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible, then throw an BugcheckException.

	static void unexpected(const char* file, int line);
		/// An exception was caught in a destructor. Break into debugger,
		/// if possible and report exception. Must only be called from
		/// within a catch () block as it rethrows the exception to
		/// determine its class.

	static void debugger(const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

	static void debugger(const char* msg, const char* file, int line);
		/// An internal error was encountered. Break into the debugger, if
		/// possible.

protected:
	static std::string what(const char* msg, const char* file, int line, const char* text = 0);
};


} // namespace Percipio


//
// useful macros (these automatically supply line number and file name)
//
#if defined(_DEBUG)
	#define percipio_assert_dbg(cond) \
		if (!(cond)) Percipio::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0

	#define percipio_assert_msg_dbg(cond, text) \
		if (!(cond)) Percipio::Bugcheck::assertion(#cond, __FILE__, __LINE__, text); else (void) 0
#else
	#define percipio_assert_msg_dbg(cond, text)
	#define percipio_assert_dbg(cond)
#endif


#define percipio_assert(cond) \
	if (!(cond)) Percipio::Bugcheck::assertion(#cond, __FILE__, __LINE__); else (void) 0


#define percipio_assert_msg(cond, text) \
	if (!(cond)) Percipio::Bugcheck::assertion(#cond, __FILE__, __LINE__, text); else (void) 0


#define percipio_check_ptr(ptr) \
	if (!(ptr)) Percipio::Bugcheck::nullPointer(#ptr, __FILE__, __LINE__); else (void) 0


#define percipio_bugcheck() \
	Percipio::Bugcheck::bugcheck(__FILE__, __LINE__)


#define percipio_bugcheck_msg(msg) \
	Percipio::Bugcheck::bugcheck(msg, __FILE__, __LINE__)


#define percipio_unexpected() \
	Percipio::Bugcheck::unexpected(__FILE__, __LINE__);


#define percipio_debugger() \
	Percipio::Bugcheck::debugger(__FILE__, __LINE__)


#define percipio_debugger_msg(msg) \
	Percipio::Bugcheck::debugger(msg, __FILE__, __LINE__)


#if defined(_DEBUG)
#	define percipio_stdout_dbg(outstr) \
	std::cout << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define percipio_stdout_dbg(outstr)
#endif


#if defined(_DEBUG)
#	define percipio_stderr_dbg(outstr) \
		std::cerr << __FILE__ << '(' << std::dec << __LINE__ << "):" << outstr << std::endl;
#else
#	define percipio_stderr_dbg(outstr)
#endif


//
// percipio_static_assert
//
// The following was ported from <boost/static_assert.hpp>
//


template <bool x>
struct PERCIPIO_STATIC_ASSERTION_FAILURE;


template <>
struct PERCIPIO_STATIC_ASSERTION_FAILURE<true>
{
	enum
	{
		value = 1
	};
};


template <int x> 
struct percipio_static_assert_test
{
};


#if defined(__GNUC__) && (__GNUC__ == 3) && ((__GNUC_MINOR__ == 3) || (__GNUC_MINOR__ == 4))
#define percipio_static_assert(B) \
	typedef char PERCIPIO_JOIN(percipio_static_assert_typedef_, __LINE__) \
        [PERCIPIO_STATIC_ASSERTION_FAILURE<(bool) (B)>::value]
#else
#define percipio_static_assert(B) \
	typedef percipio_static_assert_test<sizeof(PERCIPIO_STATIC_ASSERTION_FAILURE<(bool) (B)>)> \
		PERCIPIO_JOIN(percipio_static_assert_typedef_, __LINE__) PERCIPIO_UNUSED
#endif


#endif // Foundation_Bugcheck_INCLUDED
