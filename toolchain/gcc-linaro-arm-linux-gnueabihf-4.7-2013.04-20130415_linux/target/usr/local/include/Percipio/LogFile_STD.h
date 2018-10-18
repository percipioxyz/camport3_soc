//
// LogFile_STD.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/LogFile_STD.h#1 $
//
// Library: Foundation
// Package: Logging
// Module:  LogFile
//
// Definition of the LogFileImpl class using iostreams.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_LogFile_STD_INCLUDED
#define Foundation_LogFile_STD_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Timestamp.h"
#include "Percipio/FileStream.h"


namespace Percipio {


class Foundation_API LogFileImpl
	/// The implementation of LogFile for non-Windows platforms.
	/// The native filesystem APIs are used for
	/// total control over locking behavior.
{
public:
	LogFileImpl(const std::string& path);
	~LogFileImpl();
	void writeImpl(const std::string& text, bool flush);
	UInt64 sizeImpl() const;
	Timestamp creationDateImpl() const;
	const std::string& pathImpl() const;

private:
	std::string _path;
	mutable Percipio::FileOutputStream _str;
	Timestamp _creationDate;
};


} // namespace Percipio


#endif // Foundation_LogFile_STD_INCLUDED
