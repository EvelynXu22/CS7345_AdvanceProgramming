
#include <thread>

#include "stop.hpp"
#include "machine.hpp"
#include "shop.hpp"

void Stop::Execute(Machine *machine)
{
    // mutexLock.lock();
    while (machine->_shop->isOpen)
    {
        if (machine->_shop->CheckCapacity("A"))
        {
            machine->fsm.ChangeState(machine, &(machine->produceA));
        }
        else if (machine->_shop->CheckCapacity("B"))
        {
            machine->fsm.ChangeState(machine, &(machine->produceB));
        }

        // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
    }
    // mutexLock.unlock();
}
