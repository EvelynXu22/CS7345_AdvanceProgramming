#pragma once

#include <atomic>
#include <vector>
#include <thread>

class Machine;
class Shop;
class Command;

class Factory
{
public:
    std::atomic<bool> producing{false};
    std::vector<Machine *> machines;
    std::vector<std::thread> threads;
    std::vector<Command *> commands;

    int machineNum;

    void SetMachine(Shop *shop);
    void Produce();
    void Stop();
    void ShutDown();

    static Factory &getInstance()
    {
        static Factory instance;
        return instance;
    }

private:
    Factory(){};
    ~Factory(){};
};
