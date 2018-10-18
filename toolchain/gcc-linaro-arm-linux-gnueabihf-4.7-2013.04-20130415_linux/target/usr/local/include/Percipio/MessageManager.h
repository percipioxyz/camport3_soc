#ifndef Foundation_MessageManager_INCLUDED
#define Foundation_MessageManager_INCLUDED

#include <stdint.h>
#include <vector>
#include <map>
#include "Percipio/Mutex.h"
#include "Percipio/Fifo.h"


namespace Percipio {


class MessageManager {
public:
    class Message {
        /// This message is different from message defined in Percipio/Message.h. That
        /// message is string message only for post string.
        /// This message is for post some data or parameters.
    public:
        enum {
            MSGTYPE_UNKNOWN = -1,
        };
    
        int32_t     type;
        int32_t     timeStamp;
        void*       from;
        void*       to;
        std::vector<uint8_t> buf;
    
        Message();
        Message(int32_t _type);
        template<class T>
        Message(int32_t _type, T _param, uint64_t _timeStamp = 0, void* _from = 0, void* _to = 0);

        template<class T>
            void set(const T&);
        template<class T>
            T fetch();
    };

    enum Priority {
        MSGPRIO_LOW,    // Async, low priority
        MSGPRIO_MID,    // Async, higher priority
        MSGPRIO_HIGH,   // Async, highest priority
    };


    typedef void (*handler_t) (Message*, void*);

    MessageManager(uint32_t maxHandleThread = 0);
    ~MessageManager();

    void    registerHandler(int msgType, handler_t handler, void* arg);
    void    unregisterHandler(int msgType);

    void    run();
    void    stop();     // stop running
    void    clear();    // clear all messages

    bool    isRunning();
    void    setSleepTime(int ms);  // in milliseconds

    int     sendMessage(const Message &msg, int prio = MSGPRIO_LOW);
    int     sendMessage(int32_t type, int prio = MSGPRIO_LOW);
    template<class T>
    int     sendMessage(int32_t type, T p, int prio = MSGPRIO_LOW);

private:
    struct Callback {
        handler_t   func;
        void*       arg;
        Callback(handler_t h, void* a) : func(h), arg(a) {}
    };

    void    handleMsg(Message*);

    bool                    m_toExit;
    bool                    m_running;
    int                     m_sleepTime;
    Mutex                   m_lockLow;
    Mutex                   m_lockMid;
    Mutex                   m_lockHigh;
    Fifo<Message>*          m_lowMsg;
    Fifo<Message>*          m_midMsg;
    Fifo<Message>*          m_highMsg;

    std::map<int, Callback> m_map;
};

//
// inlines
//
inline MessageManager::Message::Message()
    : type(MSGTYPE_UNKNOWN)
    , timeStamp(0)
    , from(0)
    , to(0)
{
}

inline MessageManager::Message::Message(int32_t _type)
    : type(_type)
    , timeStamp(0)
    , from(0)
    , to(0)
{
}
    
template<class T>
inline MessageManager::Message::Message(int32_t _type, T _param, uint64_t _timeStamp
                                        , void* _from, void* _to)
    : type(_type)
    , timeStamp(_timeStamp)
    , from(_from)
    , to(_to)
{
    set<T>(_param);
}


template<class T>
inline void MessageManager::Message::set(const T& _param)
{
    buf.resize(sizeof(T));
    *(T*)&buf[0] = _param;
}


template<class T>
inline T MessageManager::Message::fetch()
{
    T* p = (T*)&buf[0];
    T v = *p;
    p->~T();
    return v;
}


inline void MessageManager::stop()
{
    m_toExit = true;
}


inline bool MessageManager::isRunning()
{
    return m_running;
}


inline int MessageManager::sendMessage(int32_t type, int prio)
{
    return sendMessage(Message(type), prio);
}


template<class T>
inline int MessageManager::sendMessage(int32_t type, T param, int prio)
{
    return sendMessage(Message(type, param), prio);
}


inline void MessageManager::registerHandler(int type, handler_t handler, void* arg)
{
    m_map.insert(std::pair<int, Callback>(type, Callback(handler, arg)));
}

inline void MessageManager::unregisterHandler(int type)
{
    m_map.erase(type);
}

inline void MessageManager::setSleepTime(int ms)
{
    m_sleepTime = ms;
}


}

#endif
