#ifndef Foundation_SignalSlot_CPP11_INCLUDED
#define Foundation_SignalSlot_CPP11_INCLUDED

#include "Percipio/Foundation.h"
#include <new>
#include <set>
#include <functional>
#include <mutex>

// macro for user to select lock in construction
#define SIGSLOT_SINGLE_THREAD_LOCK  (xyz::_ssSingleThreadLock*)0
#define SIGSLOT_MULTI_THREAD_LOCK   (xyz::_ssMultiThreadLock*)0

#ifndef SIGSLOT_DEFAULT_LOCK
#	ifdef _SIGSLOT_SINGLE_THREADED
#		define SIGSLOT_DEFAULT_LOCK _ssSingleThreadLock
#	else
#		define SIGSLOT_DEFAULT_LOCK _ssMultiThreadLock
#	endif
#endif

namespace Percipio {

class _ssThreadLock
    {
    public:
        virtual ~_ssThreadLock() {}
		virtual void lock() = 0;
		virtual void unlock() = 0;
    };

class _ssSingleThreadLock : public _ssThreadLock
	{
	public:
        _ssSingleThreadLock() {}
		virtual ~_ssSingleThreadLock() {}
		virtual void lock() {}
		virtual void unlock() {}
	};

class _ssMultiThreadLock : public _ssThreadLock
    {
        std::mutex mtx;
    public:
        _ssMultiThreadLock() {}
		virtual ~_ssMultiThreadLock() {}
		virtual void lock() { mtx.lock(); }
		virtual void unlock() { mtx.unlock(); }
    };

// class _ssCompatableLock
// {
//     struct {
//         _ssSingleThreadLock slock[0];
//         _ssMultiThreadLock  mlock[0];
//         int                 _resv[(sizeof(_ssMultiThreadLock)+3)/4];
//     } _m_lock;
// public:
//     template<class T>
//     _ssCompatableLock(const T* _x = NULL) {
//         new(&_m_lock._resv) T;
//     }
// 
//     ~_ssCompatableLock() {((_ssThreadLock*)&_m_lock.slock[0])->~_ssThreadLock();}
// 
//     void lock() {((_ssThreadLock*)&_m_lock.slock[0])->lock();}
//     void unlock() {((_ssThreadLock*)&_m_lock.slock[0])->unlock();}
// };
class _ssCompatableLock
{
	struct {
		int                 _resv[(sizeof(_ssMultiThreadLock)+3) / 4];
	} _m_lock;
public:
	template<class T>
	_ssCompatableLock(const T* _x = NULL) {
		new(&_m_lock._resv) T;
	}
	
	~_ssCompatableLock() { ((_ssThreadLock*)&_m_lock._resv)->~_ssThreadLock(); }

	void lock() { ((_ssThreadLock*)&_m_lock._resv)->lock(); }
	void unlock() { ((_ssThreadLock*)&_m_lock._resv)->unlock(); }
};

class _ssLockBlock
{
	_ssCompatableLock *m_mutex;
public:
	_ssLockBlock(_ssCompatableLock *mtx) : m_mutex(mtx) { m_mutex->lock(); }
	~_ssLockBlock() { m_mutex->unlock(); }
};

// ==================================== slot =========================================
template <typename... _ArgTypes>
struct Slot {
    unsigned long long objID;
    unsigned long long funcID;
    std::function<void(_ArgTypes...)> _func;

    Slot()
        : objID(0), funcID(0) {}

    Slot(void(*f)(_ArgTypes...))
        : objID(0), funcID((unsigned long long)(void*)f), _func(f) {}

    template <class T>
    Slot(T* pobj, void(T::*f)(_ArgTypes...))
        : objID((unsigned long long)pobj)
        , funcID((unsigned long long)(void*)f)
        , _func([=](_ArgTypes... args){pobj->f(args...);})
    {}

    Slot(const Slot<_ArgTypes...> &other){
        objID = other.objID;
        funcID = other.funcID;
        _func = other._func;
    }

    virtual ~Slot() {
        objID = 0;
        funcID = 0;
    }

    struct Less {
        bool operator() (const Slot<_ArgTypes...>* a, const Slot<_ArgTypes...>* b) {
            return a->objID < b->objID
                || (a->objID == b->objID && a->funcID < b->funcID);
        }
    };

    bool operator == (const Slot<_ArgTypes...>& other) {
        return objID == other.objID && funcID == other.funcID;
    }

    virtual void emit( _ArgTypes... args ){
        _func(args...);
    }
};

// ==================================== signal =========================================
// Signal is also a slot, so that chain signal could be created.
template <typename... _ArgTypes>
class Signal : public Slot<_ArgTypes...>
{
public:
    typedef Slot<_ArgTypes...>  slot_t;
    typedef std::set<slot_t*, typename slot_t::Less>  SlotSetType;

    template<class T = SIGSLOT_DEFAULT_LOCK>
    Signal(const T* _x = NULL) : Slot<_ArgTypes...>(), m_lock(_x)
    {
        this->objID = (unsigned long long)this;
        this->funcID = 0; // NOTE: only singals have 0 funcID
    }

    ~Signal()
    {
    }

    /// Connect same type Signal
    bool connect(Signal<_ArgTypes...>* signal)
    {
        _ssLockBlock lock(&m_lock);
        std::pair<typename SlotSetType::iterator, bool> ret = m_slots.insert(this);
        return ret.second;
    }

    /// Connect global function
    bool connect(void(*p)(_ArgTypes...))
    {
        _ssLockBlock lock(&m_lock);
        Slot<_ArgTypes...>* pSlot = new Slot<_ArgTypes...>(p);
        std::pair<typename SlotSetType::iterator, bool> ret = m_slots.insert(pSlot);
        return ret.second;
    }

    /// Connect class member function
    template<class T>
    bool connect(T* pclass, void(T::*pmemfun)(_ArgTypes...))
    {
        _ssLockBlock lock(&m_lock);
        Slot<_ArgTypes...>* pSlot = new Slot<_ArgTypes...>(pclass, pmemfun);
        std::pair<typename SlotSetType::iterator, bool> ret = m_slots.insert(pSlot);
        return ret.second;
    }

    /// Disconnect all
    void disconnectAll()
    {
		_ssLockBlock lock(&m_lock);
        for(typename SlotSetType::iterator it = m_slots.begin(); it != m_slots.end(); it++)
        {
            if((*it)->funcID != 0){ // dont delete signals
                delete *it;
            }
        }
        m_slots.clear();
    }

    /// Disconnect same type Signal
    bool disconnect(Signal<_ArgTypes...>* signal)
    {
        _ssLockBlock lock(&m_lock);
        typename SlotSetType::iterator it = m_slots.find(signal);
        if(it != m_slots.end()){
            m_slots.erase(it);
            return true;
        }
        return false;
    }

    /// Disconnect global function
    bool disconnect(void(*p)(_ArgTypes...))
    {
        _ssLockBlock lock(&m_lock);
        Slot<_ArgTypes...> slot(p);
        typename SlotSetType::iterator it = m_slots.find(&slot);
        if(it != m_slots.end()){
            delete *it;
            m_slots.erase(it);
            return true;
        }
        return false;
    }

    /// Disconnect class member function
    template<class T>
    bool disconnect(T* pclass, void(T::*pmemfun)(_ArgTypes...))
    {
        _ssLockBlock lock(&m_lock);
        Slot<_ArgTypes...> slot(pclass, pmemfun);
        typename SlotSetType::iterator it = m_slots.find(&slot);
        if(it != m_slots.end()){
            delete *it;
            m_slots.erase(it);
            return true;
        }
        return false;
    }

    /// Get number of connected slots
    inline int connectedCount()
    {
        return m_slots.size();
    }

    /// Do job
    void emit(_ArgTypes... args) {
        if(m_slots.size())
        {
		    _ssLockBlock lock(&m_lock);
            for(typename SlotSetType::iterator it = m_slots.begin(); it != m_slots.end(); it++)
            {
                (*it)->emit(args...);
            }
        }
    }

private:
    SlotSetType         m_slots;
    _ssCompatableLock   m_lock;
};

} // namespace xyz

#endif
