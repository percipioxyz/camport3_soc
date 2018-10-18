//
// AccessExpireStrategy.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/AccessExpireStrategy.h#1 $
//
// Library: Foundation
// Package: Cache
// Module:  AccessExpireStrategy
//
// Definition of the AccessExpireStrategy class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_AccessExpireStrategy_INCLUDED
#define Foundation_AccessExpireStrategy_INCLUDED


#include "Percipio/KeyValueArgs.h"
#include "Percipio/ValidArgs.h"
#include "Percipio/ExpireStrategy.h"
#include "Percipio/Bugcheck.h"
#include "Percipio/Timestamp.h"
#include "Percipio/EventArgs.h"
#include <set>
#include <map>


namespace Percipio {


template < 
	class TKey,
	class TValue
>
class AccessExpireStrategy: public ExpireStrategy<TKey, TValue>
	/// An AccessExpireStrategy implements time and access based expiration of cache entries
{
public:
	AccessExpireStrategy(Timestamp::TimeDiff expireTimeInMilliSec): ExpireStrategy<TKey, TValue>(expireTimeInMilliSec)
		/// Create an expire strategy. Note that the smallest allowed caching time is 25ms.
		/// Anything lower than that is not useful with current operating systems.
	{
	}

	~AccessExpireStrategy()
	{
	}

	void onGet(const void*, const TKey& key)
	{
		// get triggers an update to the expiration time
		typename ExpireStrategy<TKey, TValue>::Iterator it = this->_keys.find(key);
		if (it != this->_keys.end())
		{
			this->_keyIndex.erase(it->second);
			Timestamp now;
			typename ExpireStrategy<TKey, TValue>::IndexIterator itIdx =
				this->_keyIndex.insert(typename ExpireStrategy<TKey, TValue>::TimeIndex::value_type(now, key));
			it->second = itIdx;
		}
	}
};


} // namespace Percipio


#endif // Foundation_AccessExpireStrategy_INCLUDED
