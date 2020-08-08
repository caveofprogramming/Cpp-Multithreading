#include <iostream>
#include <thread>
#include <queue>

using namespace std;

template<typename E>
class blocking_queue
{
private:
    int _max_size;
    queue<E> _queue;


public:
    blocking_queue(int max_size): _max_size(max_size)
    {

    }

    void push(E e)
    {
        _queue.push(e);
    }

    E pop()
    {
        E item = _queue.front();
        _queue.pop();
        return item;
    }
};

int main()
{
    blocking_queue<int> qu(5);

    thread t1([&](){
        for(int i = 0; i < 10; i++)
        {
            qu.push(i);
        }
    });

    thread t2([&](){
        for(int i = 0; i < 10; i++)
        {
            auto item = qu.pop();
            cout << "consumed " << item << endl;
        }
    });

    t1.join();
    t2.join();
    
    return 0;
}