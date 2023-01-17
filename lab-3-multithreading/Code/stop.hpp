
#pragma once

#include <string.h>
#include "state.hpp"

class Machine;


class Stop : public State {
    public:
    std::mutex mutexLock;
    virtual void Enter(Machine * machine){};
    virtual void Execute(Machine * machine);
    virtual const char * GetName(){return name.c_str();};

    ~Stop(){};

    private:
    std::string name = "STOP";

};