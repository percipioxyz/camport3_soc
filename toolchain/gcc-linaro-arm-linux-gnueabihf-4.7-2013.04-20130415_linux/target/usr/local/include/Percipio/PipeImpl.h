//
// PipeImpl.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/PipeImpl.h#1 $
//
// Library: Foundation
// Package: Processes
// Module:  PipeImpl
//
// Definition of the PipeImpl class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_PipeImpl_INCLUDED
#define Foundation_PipeImpl_INCLUDED


#include "Percipio/Foundation.h"


#if defined(PERCIPIO_OS_FAMILY_WINDOWS)
#if defined(_WIN32_WCE)
#include "PipeImpl_DUMMY.h"
#else
#include "Percipio/PipeImpl_WIN32.h"
#endif
#elif defined(PERCIPIO_OS_FAMILY_UNIX)
#include "Percipio/PipeImpl_POSIX.h"
#else
#include "Percipio/PipeImpl_DUMMY.h"
#endif


#endif // Foundation_PipeImpl_INCLUDED
