#ifndef Foundation_FPSCounter_INCLUDED
#define Foundation_FPSCounter_INCLUDED

#include <stdint.h>
#include "Percipio/Foundation.h"
#include "Percipio/Fifo.h"

namespace Percipio {

class Foundation_API FPSCounter
{
private:
    Fifo<int64_t>   fifo;
    uint32_t        frameCount;

public:
    FPSCounter(uint32_t totalFrames = 32);
    ~FPSCounter();

    void click();
    void reset();

    float fps();
};

//
// inline
//

inline void FPSCounter::reset()
{
    fifo.reset();
}


}

#endif
