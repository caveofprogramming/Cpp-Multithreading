#include <thread>
#include <iostream>
#include <chrono>
#include "blocking_queue.h"

/**
 * Blocking queue demo
 */


int main()
{
    blocking_queue<int> qu(3);

    std::thread t1([&](){
        for(int i = 0; i < 10; i++)
        {
            std::cout << "pushing " << i << std::endl;
            std::cout << "queue size is " << qu.size() << std::endl;
            qu.push(i);
        }
    });

    std::thread t2([&](){
        for(int i = 0; i < 10; i++)
        {
            auto item = qu.front();
            qu.pop();
            std::cout << "consumed " << item << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(2));
        }
    });

    t1.join();
    t2.join();
    
    return 0;
}