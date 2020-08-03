#include <iostream>
#include <thread>
#include <atomic>
#include <chrono>
#include <mutex>

using namespace std;

int main()
{
    int count = 0;
    const int ITERATIONS = 1E6;

    mutex mtx;

    auto func = [&]() {
        for (int i = 0; i < ITERATIONS; i++)
        {
            mtx.lock();
            ++count;
            mtx.unlock();
        }
    };

    thread t1(func);
    thread t2(func);

    t1.join();
    t2.join();

    cout << count << endl;

    return 0;
}