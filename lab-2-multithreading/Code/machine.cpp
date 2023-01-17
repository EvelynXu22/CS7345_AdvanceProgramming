#include "machine.hpp"
#include <iostream>

void Machine::Work(){
    while(this->workable){
        Update();
    }
}

void Machine::ShutDown(){
    this->workable = false;
}

void Machine::Update(){
    fsm.Update(this);
}