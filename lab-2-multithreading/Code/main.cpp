
#include <thread>
#include <vector>
#include <iostream>
#include <mutex>
#include <chrono>

#include "factory.hpp"
#include "shop.hpp"
#include "customer.hpp"

#define RUN_TIMES 40

using namespace std;

// const float TARGET_INCOME = 1000;

Factory factory;
Shop& shop = Shop::getInstance();
Customer customer;

vector<double> times;
chrono::high_resolution_clock::time_point startTime, endTime;

// API
void Ready()
{
	factory.SetMachine(&shop);
	customer.CustomerReady(&shop);
}

void Set(float newTaget)
{
	shop.targetIncome = newTaget;
}

extern "C"
{

	void Start()
	{

		shop.isOpen = true;
		factory.Produce();
		customer.Shopping();
	}

	void Stop()
	{
		factory.Stop();
		customer.Stop();
	}

	void Kill()
	{
		factory.ShutDown();
		customer.LeaveAway();
	}

	void Exit()
	{
		cout << "=========================================" << endl;
		cout << RUN_TIMES << " Rounds Test End" << endl;
		cout << "\tTime Shows Down:" << endl;

		double sumtime = 0;
		for (int i = 0; i < times.size(); i++)
		{
			cout << times[i] << endl;
			sumtime += times[i];
		}
		cout << "Mean Time: " << sumtime / times.size() << endl;
	}
}

int main()
{

	factory.machineNum = thread::hardware_concurrency() - 1 - 1;
	customer.customerNum = 1;

	string command;
	mutex mainMutex;

	clock_t start, end;

	// Ready()
	shop.isOpen = true;
	factory.SetMachine(&shop);
	customer.CustomerReady(&shop);

	// Set Target Income
	Set(100000);
	cout << "=========================================" << endl;

	// Original Function Test
	/*
	bool isOpen = true;
		while (isOpen)
		{
			mainMutex.lock();
			cout << "Enter command [ready, set, start, stop, kill, exit]: " << endl;
			cin >> command;

			if (command == "set")
			{
				cout << "Enter target income:" << endl;
				cin >> shop.targetIncome;
			}
			else if (command == "ready")
			{
				shop.isOpen = true;
				factory.SetMachine(&shop);
				customer.CustomerReady(&shop);
			}
			else if (command == "start")
			{
				mainMutex.lock();
				shop.isOpen = true;
				start = clock();

				Start();

				end = clock();
				double thisTime = (double)(end - start) / CLOCKS_PER_SEC;
				cout << "\nExcution Time:" << thisTime << endl;
				times.push_back(thisTime);
				mainMutex.unlock();
			}

			else if (command == "stop")
			{
				mainMutex.lock();

				Stop();

				cout << shop.GetIncome() << endl;
				shop.SetIncome(0);
				mainMutex.unlock();
			}
			else if (command == "kill")
			{
				factory.ShutDown();
				customer.LeaveAway();
			}

			else if (command == "exit")
			{
				isOpen = false;
				for (int i = 0; i < times.size(); i++)
				{
					cout << times[i] << endl;
				}
			}
			else
			{
			}
			mainMutex.unlock();
		}
		
		*/

#ifdef __EMSCRIPTEN__
	for (int i = 0; i < RUN_TIMES; i++)
	{
		cout << "Round " << i << " Start" << endl;
		mainMutex.lock();
		startTime = chrono::high_resolution_clock::now();

		Start();

		mainMutex.unlock();
		mainMutex.lock();

		Stop();

		// Record Execution Time
		endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

		// Log Results
		cout << "\nExecution Time:" << time_span.count() << endl;
		times.push_back(time_span.count());
		cout << "\tTotal Income: " << shop.GetIncome() << endl;
		cout << "\tTotal Sold Product: " << shop.GetSoldCount() << endl;

		// Reset the states of shop
		shop.SetIncome(0);
		shop.ResetWarehouse();

		mainMutex.unlock();
		cout << "\n\tRound " << i << " End" << endl;
	}

	cout << "Emscript Test Version Finished" << endl;
	Exit();

	Kill();

#else

	for (int i = 0; i < RUN_TIMES; i++)
	{
		cout << "Round " << i << " Start" << endl;
		mainMutex.lock();
		startTime = chrono::high_resolution_clock::now();

		Start();

		mainMutex.unlock();

		mainMutex.lock();

		Stop();

		// Record Execution Time
		endTime = chrono::high_resolution_clock::now();
		chrono::duration<double> time_span = chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime);

		// Log Results
		cout << "\nExecution Time:" << time_span.count() << endl;
		times.push_back(time_span.count());
		cout << "\tTotal Income: " << shop.GetIncome() << endl;
		cout << "\tTotal Sold Product: " << shop.GetSoldCount() << endl;

		// Reset the states of shop
		shop.SetIncome(0);
		shop.ResetWarehouse();

		mainMutex.unlock();
		cout << "\n\tRound " << i << " End" << endl;
	}

	cout << "C++ Test Version Finished" << endl;
	Exit();

	Kill();

#endif
}
// }
