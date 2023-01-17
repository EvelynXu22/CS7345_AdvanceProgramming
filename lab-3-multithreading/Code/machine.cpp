#include "machine.hpp"
#include <iostream>
#include <thread>

void Machine::Work(){

    while(this->workable){
        // std::cout << "Work " << this->fsm.currentState->GetName() << std::endl;
        // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
        Update();
        // std::cout  << " Workable? " << this->workable << std::endl;
    }
}

void Machine::ShutDown(){
    fsm.ChangeState(this, &(this->stop));
    this->workable = false;
}

void Machine::Update(){
    fsm.Update(this);
}