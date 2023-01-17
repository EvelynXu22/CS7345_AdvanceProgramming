#include <thread>

#include "machine.hpp"
#include "produceB.hpp"
#include "product.hpp"
#include "shop.hpp"

void ProduceB::Execute(Machine *machine)
{

    if (machine->_shop->CheckCapacity("B"))
    {
        Product newProduct("B");
        // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
        machine->_shop->Stock(newProduct);
    }
    else
    {
        machine->fsm.ChangeState(machine, &(machine->stop));
    }

}