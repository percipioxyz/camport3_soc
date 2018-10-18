//
// ExpireLRUCache.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/ExpireLRUCache.h#1 $
//
// Library: Foundation
// Package: Cache
// Module:  ExpireLRUCache
//
// Definition of the ExpireLRUCache class.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_ExpireLRUCache_INCLUDED
#define Foundation_ExpireLRUCache_INCLUDED


#include "Percipio/AbstractCache.h"
#include "Percipio/StrategyCollection.h"
#include "Percipio/ExpireStrategy.h"
#include "Percipio/LRUStrategy.h"


namespace Percipio {


template < 
	class TKey,
	class TValue,
	class TMutex = FastMutex, 
	class TEventMutex = FastMutex
>
class ExpireLRUCache: public AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex>
	/// An ExpireLRUCache combines LRU caching and time based expire caching.
	/// It cache entries for a fixed time period (per default 10 minutes)
	/// but also limits the size of the cache (per default: 1024).
{
public:
	ExpireLRUCache(long cacheSize = 1024, Timestamp::TimeDiff expire = 600000): 
		AbstractCache<TKey, TValue, StrategyCollection<TKey, TValue>, TMutex, TEventMutex>(StrategyCollection<TKey, TValue>())
	{
		this->_strategy.pushBack(new LRUStrategy<TKey, TValue>(cacheSize));
		this->_strategy.pushBack(new ExpireStrategy<TKey, TValue>(expire));
	}

	~ExpireLRUCache()
	{
	}

private:
	ExpireLRUCache(const ExpireLRUCache& aCache);
	ExpireLRUCache& operator = (const ExpireLRUCache& aCache);
};


} // namespace Percipio


#endif // Foundation_ExpireLRUCache_INCLUDED
