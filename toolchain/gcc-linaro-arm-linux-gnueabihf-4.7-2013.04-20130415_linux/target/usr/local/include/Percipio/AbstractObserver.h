//
// AbstractObserver.h
//
// $Id: //percipio/1.4/Foundation/include/Percipio/AbstractObserver.h#2 $
//
// Library: Foundation
// Package: Notifications
// Module:  NotificationCenter
//
// Definition of the AbstractObserver class.
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef Foundation_AbstractObserver_INCLUDED
#define Foundation_AbstractObserver_INCLUDED


#include "Percipio/Foundation.h"
#include "Percipio/Notification.h"


namespace Percipio {


class Foundation_API AbstractObserver
	/// The base class for all instantiations of
	/// the Observer and NObserver template classes.
{
public:
	AbstractObserver();
	AbstractObserver(const AbstractObserver& observer);
	virtual ~AbstractObserver();
	
	AbstractObserver& operator = (const AbstractObserver& observer);

	virtual void notify(Notification* pNf) const = 0;
	virtual bool equals(const AbstractObserver& observer) const = 0;
	virtual bool accepts(Notification* pNf) const = 0;
	virtual AbstractObserver* clone() const = 0;
	virtual void disable() = 0;
};


} // namespace Percipio


#endif // Foundation_AbstractObserver_INCLUDED
