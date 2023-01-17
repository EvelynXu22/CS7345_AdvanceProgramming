#include <stdio.h>
#include <iostream>

#include "factory.hpp"
#include "machine.hpp"
#include "shop.hpp"
#include "command.hpp"

using namespace std;

void Factory::SetMachine(Shop* shop){
    for(int i = 0; i < this->machineNum; i++){
        this->machines.push_back(new Machine(shop));

        this->commands.push_back(new Command(this->machines[i], &Machine::Work));

        this->machines[i]->fsm.currentState = &this->machines[i]->stop;
    }
    cout << "Set " << this->machines.size() << " Machines" << endl;
}

void Factory::Produce(){
    this->producing = true;

    cout << "Starting Machines (Thread)" << std::endl;

    for (int i = 0; i < machines.size(); i++){
        this->machines[i]->workable = true;
    
        this->threads.push_back(thread(&Command::execute, this->commands[i]));

        cout << "Machine ID: " << this->threads[i].get_id() << " Online" << endl;
        
        // Delay 1 miliseconds betwwen creating threads
        // this_thread::sleep_for(std::chrono::milliseconds(1*1000));
        this_thread::sleep_for(std::chrono::milliseconds(1));
    }
    cout << "Started " << this->threads.size() << " Machines" << endl;
}

void Factory::Stop(){
    for (int i = 0; i < this->machineNum; i++){
        // Stop the individual machine
        this->machines[i]->workable = false;
    }

    // Clean up threads
    std::vector<std::thread>::iterator thptr;
    for(thptr = this->threads.end(); thptr >= this-> threads.begin(); thptr--){
        if(thptr->joinable()){
            thptr->join();
            this->threads.erase(thptr);
        }
    }

    std::cout<< "\tThere are " << this->threads.size() << " threads left." << std::endl;
}

void Factory::ShutDown(){
    this->producing = false;

    // Make sure all threads are stopped
    if(this->threads.size() > 0){
        this->Stop();
    }

    // Delete all Machine
    for (int i = this->machines.size()-1; i >= 0; i--)
    {
        this->machines[i]->ShutDown();
        delete this->machines[i];
        this->machines[i] = nullptr;
    }

    this->machines.clear();
    std::cout<< "\tThere are " << this->machines.size() << " Machines left. " << std::endl;
}