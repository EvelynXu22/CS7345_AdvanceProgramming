

#pragma once
#include <atomic>
#include <thread>
#include <iostream>
#include <mutex>

#include "shop.hpp"

class Shop;

class People
{
public:
    std::atomic<bool> shopping{false};
    std::mutex mutexLock;

    void Shopping()
    {
        while (shopping && _shop->isOpen)
        {
            // mutexLock.lock();
            // std::lock_guard<std::mutex> guard(mutexLock);
            // unique_lock<mutex> locker(mutexLock);
            if (_shop->CheckInStock("A"))
            {
                _shop->Sold("A");
                // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
            }
            else if (_shop->CheckInStock("B"))
            {
                _shop->Sold("B");
                // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
            }
            else
            {
                
            }
        }
    };
    void Leave()
    {
        // mutexLock.lock();
        this->shopping = false;
        // mutexLock.unlock();
        // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
        // Shopping();
    }

    People();
    People(Shop *shop)
    {
        _shop = shop;
    }

private:
    Shop *_shop;
};