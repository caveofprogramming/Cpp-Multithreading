#include <iostream>
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <chrono>
#include <vector>
#include <functional>
#include <future> 

using namespace std;

template <typename E>
class blocking_queue
{
private:
    mutex _mtx;
    condition_variable _cond;
    int _max_size;
    queue<E> _queue;

public:
    blocking_queue(int max_size) : _max_size(max_size)
    {
    }

    void push(E e)
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this]() -> _queue.size() < _max_size);

        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E front()
    {
        unique_lock<mutex> lock(_mtx);
        E item = _queue.front();
        return item;
    }

    void pop()
    {
        unique_lock<mutex> lock(_mtx);

        _cond.wait(lock, [this]() -> !_queue.empty());
        _queue.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size()
    {
        return _queue.size();
    }
};

int work(int id)
{
    cout << id << " working" << endl;
    this_thread::sleep_for(chrono::milliseconds(1000));
    return id * 100;
}

int main()
{
    blocking_queue<int> qu(3);

    for(int i = 0; i < 10; i++)
    {
        packaged_task<int(int)> task(work);

        thread t(move(task), i);

        int result = task.get_future().get();

        qu.push(result);
    }

    return 0;
}