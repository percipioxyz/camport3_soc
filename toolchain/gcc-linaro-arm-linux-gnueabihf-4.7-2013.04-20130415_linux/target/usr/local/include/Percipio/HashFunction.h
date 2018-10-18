//
// HashFunction.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/HashFunction.h#1 $
//
// Library: Foundation
// Package: Hashing
// Module:  HashFunction
//
// Definition of the HashFunction class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_HashFunction_INCLUDED
#define Foundation_HashFunction_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Hash.h"


namespace Percipio {


//@ deprecated
template <class T>
struct HashFunction
	/// A generic hash function.
{
	UInt32 operator () (T key, UInt32 maxValue) const
		/// Returns the hash value for the given key.
	{
		return static_cast<UInt32>(Percipio::hash(key)) % maxValue;
	}
};


//@ deprecated
template <>
struct HashFunction<std::string>
	/// A generic hash function.
{
	UInt32 operator () (const std::string& key, UInt32 maxValue) const
		/// Returns the hash value for the given key.
	{
		return static_cast<UInt32>(Percipio::hash(key)) % maxValue;
	}
};


} // namespace Percipio


#endif // Foundation_HashFunctions_INCLUDED
