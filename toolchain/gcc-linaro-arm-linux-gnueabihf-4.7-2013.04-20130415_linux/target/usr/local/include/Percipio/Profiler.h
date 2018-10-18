#ifndef Foundation_Profiler_INCLUDED
#define Foundation_Profiler_INCLUDED


#include <string>
#include "Percipio/Foundation.h"


namespace Percipio {


class Profiler {
    class ProfilerImpl;

    ProfilerImpl* impl;

public:
    static void gClear();
    static void gBegin(int index);
    static bool gRunning(int index);
    static void gEnd(int index);
    static std::string gDump();

    Profiler();
    ~Profiler();

    void clear();
    void begin(int index);
    bool running(int index);
    void end(int index);

    std::string dump();
};


}

#endif
