#ifndef Foundation_Dispatcher_INCLUDED
#define Foundation_Dispatcher_INCLUDED


#include <set>
#include "Percipio/Listener.h"
#include "Percipio/Mutex.h"


namespace Percipio {


template<class T>
class Dispatcher
    /// Dispatcher is also a container of T, user should
    /// set the _val before dispatch. And listeners should
    /// never modify the _val.
{
public:
    T       _val;

    void addListener(Listener*);
    void removeListener(Listener*);

    size_t numberOfListeners() const;
    void dispatch();

private:
    Mutex                   _lock;
    std::set<Listener*>     _listeners;
};

// 
// inlines
// 
template<class T>
inline void Dispatcher<T>::addListener(Listener* l)
{
    Mutex::ScopedLock _l(_lock);
    _listeners.insert(l);
}


template<class T>
inline void Dispatcher<T>::removeListener(Listener* l)
{
    Mutex::ScopedLock _l(_lock);
    _listeners.erase(l);
}


template<class T>
inline size_t Dispatcher<T>::numberOfListeners() const
{
    return _listeners.size();
}

template<class T>
inline void Dispatcher<T>::dispatch()
{
    if(_listeners.size() > 0){
        Mutex::ScopedLock _l(_lock);

        for(std::set<Listener*>::iterator it = _listeners.begin();
                it != _listeners.end(); it++)
        {
            try {
                (*it)->notify(&_val);
            } catch (Percipio::Exception& e) {
                _listeners.erase(*it);
            }
        }
    }
}


}

#endif
