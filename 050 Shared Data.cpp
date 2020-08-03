#include <iostream>
#include <thread>
#include <atomic> 
#include <chrono>

using namespace std;

/*
 * When is multithreading useful?
 * 
 * 1. When you're waiting for something external and want to execute code meanwhile.
 * (asynchronous execution)
 * 
 * Example: pinging remote servers
 * Example: drawing graphics while also processing user input
 * 
 * 2. Distributing processing across multiple cores
 * 
 * Example: calculating pi to lots of digits
 * 
 */

int main()
{
    atomic<int> count = 0;
    const int ITERATIONS = 1E6;

    thread t1([&count](){
        for(int i = 0; i < ITERATIONS; i++)
        {
            ++count;
        }
    });

    thread t2([&count](){
        for(int i = 0; i < ITERATIONS; i++)
        {
            ++count;
        }
    });

    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}