#pragma once

#include <atomic>
#include <vector>
#include <thread>

class People;
class Shop;
class Command;

class Customer {
    public:
    std::atomic<bool> shopping{false};
    std::vector<People *> customers;
    std::vector<std::thread> threads;
    std::vector<Command *> commands;

    int customerNum;

    void CustomerReady(Shop * shop);
    void Shopping();
    void Stop();
    void LeaveAway();

};