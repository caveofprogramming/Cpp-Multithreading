#ifndef BLOCKING_QUEUE_INCLUDED
#define BLOCKING_QUEUE_INCLUDED

/**
 * A simple blocking queue.
 * 
 * Use push() to add items, pop() to remove items, and front()
 * to get the item at the front of the queue.
 * 
 * See blocking_queue_demo.cpp for example.
 * 
 */

#include <queue>
#include <mutex>
#include <condition_variable>

template<typename E>
class blocking_queue
{
private:
    std::mutex _mtx;
    std::condition_variable _cond;
    int _max_size;
    std::queue<E> _queue;

public:
    blocking_queue(int max_size): _max_size(max_size)
    {

    }

    void push(E e)
    {
        std::unique_lock<std::mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return _queue.size() < _max_size; });

        _queue.push(e);

        lock.unlock();
        _cond.notify_one();
    }

    E front()
    {
        std::unique_lock<std::mutex> lock(_mtx);
         _cond.wait(lock, [this](){ return !_queue.empty(); });

        return _queue.front();
    }

    void pop()
    {
        std::unique_lock<std::mutex> lock(_mtx);

        _cond.wait(lock, [this](){ return !_queue.empty(); });

        _queue.pop();

        lock.unlock();
        _cond.notify_one();
    }

    int size()
    {
        std::lock_guard<std::mutex> lock(_mtx);
        return _queue.size();
    }
};

#endif