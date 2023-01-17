#include <thread>

#include "produceA.hpp"
#include "machine.hpp"
#include "product.hpp"
#include "shop.hpp"

void ProduceA::Execute(Machine *machine)
{

    if (machine->_shop->CheckCapacity("A"))
    {
        Product newProduct("A");
        // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
        machine->_shop->Stock(newProduct);
    }
    else
    {
        machine->fsm.ChangeState(machine, &(machine->stop));
    }

}
