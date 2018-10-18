#include <string>
#include <vector>
#include "Percipio/SimpleCLog.h"
#include "Percipio/Timestamp.h"



namespace Percipio {



class TimeTick {
    struct tick_data{
        std::string name;
        int64_t     time;

        tick_data(const std::string& _name, int64_t _time) : name(_name), time(_time) {}
    };

    std::vector<tick_data> t;

public:
    void        tick(const std::string& name = std::string());
    std::string name(int index);
    int64_t     time(int index);
    void        clear();
    void        dump(bool diff = true);
};

//
// inline
//
void TimeTick::clear() {
    t.clear();
}

std::string TimeTick::name(int index) {
    return t[index].name;
}

int64_t TimeTick::time(int index) {
    return t[index].time;
}

void TimeTick::tick(const std::string& name) {
    t.push_back(tick_data(name, Timestamp().raw()));
}

void TimeTick::dump(bool diff) {
    if(diff){
        for(int i = 1; i < (int)t.size(); i++){
            LOGI("tick %d %s: %lld", i, t[i].name.c_str() , t[i].time - t[i-1].time);
        }
    } else {
        for(int i = 0; i < (int)t.size(); i++){
            LOGI("tick %d %s: %lld", i, t[i].name.c_str() , t[i].time);
        }
    }
}



}

