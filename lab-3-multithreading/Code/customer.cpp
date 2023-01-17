
#include <iostream>

#include "command.hpp"
#include "customer.hpp"
#include "people.hpp"

void Customer::CustomerReady(Shop *shop)
{
    for (int i = 0; i < this->customerNum; i++)
    {
        this->customers.push_back(new People(shop));

        this->commands.push_back(new Command(this->customers[i], &People::Shopping));
    }
    cout << this->customers.size() << " Customer is Ready" << endl;
}

void Customer::Shopping()
{
    this->shopping = true;

    cout << "Customers Start Shopping (Thread)" << std::endl;

    for (int i = 0; i < this->customerNum; i++)
    {
        this->customers[i]->shopping = true;

        this->threads.push_back(thread(&Command::execute2, this->commands[i]));
        cout << "Customer ID: " << this->threads[i].get_id() << "Online" << endl;

        // Delay 1 sec betwwen creating threads
        // this_thread::sleep_for(std::chrono::milliseconds(1 * 1000));
    }
    cout << "Arrived " << this->threads.size() << " Customers" << endl;
}

void Customer::Stop()
{
    for (int i = 0; i < this->customerNum; i++)
    {
        // Stop the individual machine
        this->customers[i]->shopping = false;
    }
    // Clean up threads
    std::vector<std::thread>::iterator thptr;
    for (thptr = this->threads.end(); thptr >= this->threads.begin(); thptr--)
    {
        // cout << "Stop thread" << endl;
        if (thptr->joinable())
        {
            thptr->join();
            this->threads.erase(thptr);
        }
    }

    std::cout << "\tThere are " << this->threads.size() << " threads left." << std::endl;
}

void Customer::LeaveAway()
{
    this->shopping = false;

    // Make sure all threads are stopped
    if (this->threads.size() > 0)
    {
        this->Stop();
    }

    // Delete all Machine
    for (int i = this->customers.size() - 1; i >= 0; i--)
    {
        this->customers[i]->Leave();
        delete this->customers[i];
        this->customers[i] = nullptr;
    }

    this->customers.clear();
    std::cout << "\tThere are " << this->customers.size() << " Customers left. " << std::endl;
}
