#include <iostream>
#include <thread>

using namespace std;

template<typename E>
class blocking_queue
{
public:
    void push(E e)
    {
        cout << "push" << endl;
    }

    void pop()
    {
        cout << "pop" << endl;
    }
};

int main()
{
    blocking_queue<int> qu;

    thread t1(&blocking_queue<int>::push, &qu, 7);
    thread t2(&blocking_queue<int>::pop, &qu);

    t1.join();
    t2.join();
    
    return 0;
}