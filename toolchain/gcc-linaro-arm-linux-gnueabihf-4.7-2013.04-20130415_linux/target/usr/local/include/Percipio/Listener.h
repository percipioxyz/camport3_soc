#ifndef Foundation_Listener_INCLUDED
#define Foundation_Listener_INCLUDED


#include "Percipio/Foundation.h"


namespace Percipio {


class Listener
{
public:
    virtual void notify(const void*) = 0;
};


}

#endif
