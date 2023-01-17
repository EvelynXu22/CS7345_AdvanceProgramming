#pragma once

class Machine;
class Shop;
class State;

class FSM {
    public:

    void Update(Machine * machine);
    void ChangeState(Machine * machine, State * nextState);
    State * currentState;
    State * previousState;

    ~FSM(){};
};