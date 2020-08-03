#include <iostream>
#include <thread>
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

void work()
{
    for (int i = 0; i < 10; i++)
    {
        this_thread::sleep_for(chrono::milliseconds(500));
        cout << "Loop " << i << endl;
    }
}

int main()
{
    thread t1(work);
    thread t2(work);

    t1.join();
    t2.join();

    return 0;
}