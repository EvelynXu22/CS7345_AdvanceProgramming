

#pragma once

#include <string.h>
#include "state.hpp"

class Machine;

class ProduceB : public State {
    public:
    std::mutex mutexLock;    
    virtual void Execute(Machine * machine);
    virtual const char * GetName(){return name.c_str();};

    private:
    std::string name = "PRODUCE B";

};