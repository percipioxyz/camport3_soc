//
// LogFile_VMS.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/LogFile_VMS.h#1 $
//
// Library: Foundation
// Package: Logging
// Module:  LogFile
//
// Definition of the LogFileImpl class using C I/O with OpenVMS extensions.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_LogFile_VMS_INCLUDED
#define Foundation_LogFile_VMS_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Timestamp.h"
#include <stdio.h>


namespace Percipio {


class Foundation_API LogFileImpl
	/// The implementation of LogFile for OpenVMS.
	/// The C Standard Library functions for file I/O
	/// are used with OpenVMS-specific extensions to
	/// control sharing and locking behavior.
{
public:
	LogFileImpl(const std::string& path);
	~LogFileImpl();
	void writeImpl(const std::string& text, bool flush);
	UInt64 sizeImpl() const;
	Timestamp creationDateImpl() const;
	const std::string& pathImpl() const;

private:
	std::string   _path;
	mutable FILE* _file;
	Timestamp     _creationDate;
};


} // namespace Percipio


#endif // Foundation_LogFile_VMS_INCLUDED
