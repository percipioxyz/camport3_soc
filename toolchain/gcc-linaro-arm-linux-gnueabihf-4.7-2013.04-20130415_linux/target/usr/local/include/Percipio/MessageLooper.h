#ifndef Foundation_MessageLooper_INCLUDED
#define Foundation_MessageLooper_INCLUDED

#include "Percipio/MessageManager.h"
#include "Percipio/Mutex.h"
#include "Percipio/Thread.h"

namespace Percipio {

class MessageLooper : public MessageManager {
 public:
  MessageLooper();

  void start();
  void stop();

  bool isRunning() {
    Percipio::Mutex::ScopedLock l(_mutex);
    return _running;
  }

  // inherited public methods of MessageManager

 private:
  class LocalRunnable : public Runnable {
   public:
    LocalRunnable(MessageLooper* looper) : _looper(looper) {}
    virtual void run() { _looper->run(); }

    MessageLooper* _looper;
  };

  mutable bool _running;
  LocalRunnable _runner;
  Thread _thread;
  Mutex _mutex;
};

}  // namespace Percipio

#endif
