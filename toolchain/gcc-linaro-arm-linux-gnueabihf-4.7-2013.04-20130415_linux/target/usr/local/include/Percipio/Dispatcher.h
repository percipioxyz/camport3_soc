#ifndef Foundation_Dispatcher_INCLUDED
#define Foundation_Dispatcher_INCLUDED


#include <set>
#include "Percipio/Listener.h"


namespace Percipio {


class Dispatcher
{
public:
    void addListener(Listener*);
    void removeListener(Listener*);

    size_t numberOfListeners() const;
    void dispatch(const void*) const;

private:
    std::set<Listener*>     _listeners;
};

// 
// inlines
// 
inline void Dispatcher::addListener(Listener* l)
{
    _listeners.insert(l);
}


inline void Dispatcher::removeListener(Listener* l)
{
    _listeners.erase(l);
}


inline size_t Dispatcher::numberOfListeners() const
{
    return _listeners.size();
}

inline void Dispatcher::dispatch(const void* val) const
{
    for(std::set<Listener*>::iterator it = _listeners.begin();
            it != _listeners.end(); it++)
    {
        (*it)->notify(val);
    }
}


}

#endif
