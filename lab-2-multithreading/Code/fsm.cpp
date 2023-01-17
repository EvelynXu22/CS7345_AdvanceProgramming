
#include "fsm.hpp"
#include "machine.hpp"
#include "state.hpp"
#include "shop.hpp"

void FSM::Update(Machine * machine){
    currentState->Execute(machine);
}

void FSM::ChangeState(Machine * machine, State * nextState){

    // Exit current state
    currentState->Exit(machine);

    // Save States in FSM
    previousState = currentState;
    currentState = nextState;

    //Update to new state
    currentState->Enter(machine);
    currentState->Execute(machine);
}