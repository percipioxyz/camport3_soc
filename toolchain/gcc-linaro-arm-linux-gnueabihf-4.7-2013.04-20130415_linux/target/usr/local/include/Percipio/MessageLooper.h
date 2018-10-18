#ifndef Foundation_MessageLooper_INCLUDED
#define Foundation_MessageLooper_INCLUDED


#include "Percipio/MessageManager.h"
#include "Percipio/Thread.h"


namespace Percipio {


class MessageLooper : public MessageManager
{
public:
    MessageLooper();

    void start();
    void stop();

    // inherited public methods of MessageManager

private:
    class LocalRunnable : public Runnable
    {
    public:
        LocalRunnable(MessageLooper* looper) : _looper(looper) {}
        virtual void run() {
            _looper->run();
        }

        MessageLooper*  _looper;
    };

    LocalRunnable   _runner;
    Thread          _thread;
};


}

#endif
