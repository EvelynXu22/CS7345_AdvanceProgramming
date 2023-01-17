
#include "fsm.hpp"
#include "machine.hpp"
#include "state.hpp"
#include "shop.hpp"

#include <iostream>

void FSM::Update(Machine * machine){
    
    // std::cout << "Update " << currentState->GetName() << std::endl;
    currentState->Execute(machine);
}

void FSM::ChangeState(Machine * machine, State * nextState){

    // Exit current state
    // currentState->Exit(machine);

    // Save States in FSM
    // std::cout << "Update " << machine->fsm.currentState->GetName() << std::endl;
    previousState = currentState;
    currentState = nextState;

    std::cout << "Change State to " << nextState->GetName() << std::endl;
    //Update to new state
    currentState->Enter(machine);
    currentState->Execute(machine);
}