#include <thread>

#include <iostream>

#include "produceA.hpp"
#include "machine.hpp"
#include "product.hpp"
#include "shop.hpp"

void ProduceA::Enter(Machine *machine)
{
    machine->data = 0.0;
}

void ProduceA::Execute(Machine *machine)
{

    if (machine->_shop->CheckCapacity("A"))
    {
        machine->data += 0.001;
        // std::cout << "Produce A " << machine->data << std::endl;
        // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
        if (machine->data > 200.0)
        {
            machine->_shop->Stock(Product("A"));
            machine->data = 0.0;
        }
    }
    else
    {
        std::cout << "Capacity of A Full" << std::endl;
        machine->fsm.ChangeState(machine, &(machine->stop));
    }
}
