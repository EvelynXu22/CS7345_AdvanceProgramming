
#pragma once
#include <string>
#include <mutex>

class Machine;
class Shop;

class State{
    public:
    virtual void Execute(Machine * machine){};
    virtual const char * GetName(){return name.c_str();};

    virtual ~State(){};
    
    private:
    std::string name = "BASE";
};