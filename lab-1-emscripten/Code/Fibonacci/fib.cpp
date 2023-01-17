#include <iostream>

#define N 35 // Output N Fibonacci numbers

using namespace std;

int fibArray[N];

int fib(int i)
{ // Recursively get Fibonacci number
    if (i < 2)
        return i == 1;
    return fib(i - 1) + fib(i - 2);
}

extern "C"
{
    int getFib()
    {
        // static int fibArray[N];
        for (int i = 1; i < N; i++)
        {
            fibArray[i] = fib(i);
        }
        return 1;
    }
}

int main(int argc, const char *argv[])
{
    clock_t start, end;
    double time[100];
    cout << "Display the Fibonacci sequence recursively:" << endl;

    for (int i = 0; i <100; i++){
        start = clock();
        int res = getFib();
        end = clock();
        time[i] =  (double)(end - start)/CLOCKS_PER_SEC;
    }


    for (int i = 0; i < 100; i++)
    {
        cout << time[i] << endl;
    }
    cout << "Fibonacci Finished"<< endl;
    // cout << "Runtime:" << (double)(end - start) / CLOCKS_PER_SEC << endl;

    return 0;
}
