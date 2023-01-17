/*
 * @Author: Teriri 89703261+EvelynXu22@users.noreply.github.com
 * @Date: 2022-10-26 16:26:11
 * @LastEditors: Teriri 89703261+EvelynXu22@users.noreply.github.com
 * @LastEditTime: 2022-10-27 14:39:00
 * @FilePath: /lab-3-multithreading-EvelynXu22/Code/stop.cpp
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */

#include <thread>

#include <iostream>

#include "stop.hpp"
#include "machine.hpp"
#include "shop.hpp"

void Stop::Execute(Machine * machine)
{
    // mutexLock.lock();
    if(machine->_shop->isOpen)
    {
        if (machine->_shop->CheckCapacity("A"))
        {
            std::cout <<" Stop to Produce A" << std::endl;
            machine->fsm.ChangeState(machine, &(machine->produceA));
        }
        else if (machine->_shop->CheckCapacity("B"))
        {
            std::cout << "Stop to Produce B" << std::endl;
            machine->fsm.ChangeState(machine, &(machine->produceB));
        }

        // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
    }
    // mutexLock.unlock();
}
