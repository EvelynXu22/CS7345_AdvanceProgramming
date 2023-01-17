
#include <iostream>

#include "shop.hpp"
#include "product.hpp"

bool Shop::CheckCapacity(string name)
{
    if (name == "A")
    {
        return this->counterA < this->capacity;
    }
    else if (name == "B")
    {
        return this->counterB < this->capacity;
    }
    else
    {
        std::cout << "Wrong Name!" << std::endl;
        return false;
    }
}

bool Shop::CheckInStock(string name)
{
    if (name == "A")
    {
        return this->counterA > 0;
    }
    else if (name == "B")
    {
        return this->counterB > 0;
    }
    else
    {
        std::cout << "Wrong Name!" << std::endl;
        return false;
    }
}

void Shop::Stock(Product product)
{
    // mutexLock.lock();
    // unique_lock<mutex> lockg2(mutexLock, try_to_lock);
    std::lock_guard<std::mutex> guard(mutexLock);
    if (product._name == "A")
    {
        this->warehouseA.push(product);
        this->counterA++;
    }
    else if (product._name == "B")
    {
        this->warehouseB.push(product);
        this->counterB++;
    }
    cout << "Stock Product " << product._name << endl;
    cout << "Capacity A: " << this->counterA << "\tCapacity B: " << this->counterB << endl;
    // mutexLock.unlock();
}

void Shop::Sold(string name)
{
    // mutexLock.lock();
    // unique_lock<mutex> lockg2(mutexLock, try_to_lock);
    std::lock_guard<std::mutex> guard(mutexLock);
    Product tmp;
    if (name == "A")
    {
        tmp = this->warehouseA.front();
        this->warehouseA.pop();
        this->counterA--;
        cout << "Sold Product A" << endl;
    }
    else if (name == "B")
    {
        tmp = this->warehouseB.front();
        this->warehouseB.pop();
        this->counterB--;
        cout << "Sold Product B" << endl;
    }
    this->income += tmp._price;
    this->soldcounter += 1;
    cout << "Now income: " << this->income << endl;
    if (income > targetIncome)
    {
        this->isOpen = false;
    }
    // mutexLock.unlock();
}

void Shop::SetIncome(float newIncome)
{
    this->income = newIncome;
}

void Shop::ResetWarehouse()
{
    this->warehouseA.empty();
    this->warehouseB.empty();

    this->counterA = 0;
    this->counterB = 0;
}