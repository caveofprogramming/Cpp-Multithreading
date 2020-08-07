#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;

int main()
{
    bool ready = false;
    mutex mtx;

    thread t1([&](){
        this_thread::sleep_for(chrono::milliseconds(2000));

        unique_lock<mutex> lock(mtx);
        ready = true;
    });

    t1.join();

    while(!ready)
    {
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    cout << "ready " << ready << endl;

    return 0;
}