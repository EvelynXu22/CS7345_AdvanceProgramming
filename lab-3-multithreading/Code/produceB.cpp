#include <thread>

#include <iostream>

#include "machine.hpp"
#include "produceB.hpp"
#include "product.hpp"
#include "shop.hpp"

void ProduceB::Enter(Machine *machine)
{
    machine->data = 0.0;
}

void ProduceB::Execute(Machine *machine)
{

    if (machine->_shop->CheckCapacity("B"))
    {
        machine->data += 0.001;

        // std::cout << "Produce B" << machine->data << std::endl;
        if (machine->data > 200.0)
        {
            // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
            machine->_shop->Stock(Product("B"));
        }
    }
    else
    {
        std::cout << "Capacity of B Full" << std::endl;
        machine->fsm.ChangeState(machine, &(machine->stop));
    }
}