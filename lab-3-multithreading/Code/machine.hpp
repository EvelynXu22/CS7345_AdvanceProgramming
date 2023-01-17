#pragma once
#include <atomic>

#include "state.hpp"
#include "fsm.hpp"
#include "produceA.hpp"
#include "produceB.hpp"
#include "stop.hpp"
#include "shop.hpp"

class Shop;

class Machine {

    friend class ProduceA;
    friend class ProduceB;
    friend class Stop;
    
    public:
    double data = 0.0;
    std::atomic<bool> workable{false};

    void Work();
    void ShutDown();
    void Update();

    Machine();
    Machine(Shop * shop){
        _shop = shop;
    }

    FSM fsm;
    ProduceA produceA;
    ProduceB produceB;
    Stop stop;

    private:
    State state;
    Shop * _shop;

};