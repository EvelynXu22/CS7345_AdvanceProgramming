#pragma once
#include <queue>
#include <string.h>
#include <atomic>
#include <mutex>

#include "product.hpp"

class Shop
{

public:
    std::atomic<bool> isOpen{false};
    std::mutex mutexLock;
    float targetIncome = 100;

    void Stock(Product product);
    void Sold(string name);
    float GetIncome() { return income; };
    void SetIncome(float newIncome);
    void ResetWarehouse();
    bool CheckCapacity(string name);
    bool CheckInStock(string name);
    int GetSoldCount() { return soldcounter; };

    static Shop &getInstance()
    {
        static Shop instance;
        return instance;
    }

private:
    float income = 0.0;
    int capacity = 20;
    std::atomic_int soldcounter = {0};
    std::atomic_int counterA = {0};
    std::atomic_int counterB = {0};
    queue<Product> warehouseA;
    queue<Product> warehouseB;

    // static Shop instance;
    Shop(){};
    ~Shop(){};
};
