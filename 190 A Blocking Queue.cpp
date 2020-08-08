#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

using namespace std;

template<typename E>
class blocking_queue
{
private:
    mutex _mtx;
    condition_variable _cond;
    int _max_size;
    queue<E> _queue;


public:
    blocking_queue(int max_size): _max_size(max_size)
    {

    }

    void push(E e)
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return _queue.size() < _max_size; });

        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E pop()
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return !_queue.empty(); });

        E item = _queue.front();
        _queue.pop();

        lock.unlock();
        _cond.notify_one();

        return item;
    }

    int size()
    {
        return _queue.size();
    }
};

int main()
{
    blocking_queue<int> qu(3);

    thread t1([&](){
        for(int i = 0; i < 10; i++)
        {
            cout << "pushing " << i << endl;
            cout << "queue size is " << qu.size() << endl;
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