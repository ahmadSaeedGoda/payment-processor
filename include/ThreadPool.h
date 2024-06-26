#ifndef THREADPOOL_H
#define THREADPOOL_H

#include <vector>
#include <thread>
#include <queue>
#include <functional>
#include <mutex>
#include <condition_variable>
#include <future>
#include <stdexcept>

using namespace std;

class ThreadPool
{
public:
    ThreadPool(size_t);
    template <class F, class... Args>
    auto enqueue(F &&f, Args &&...args) -> future<typename invoke_result<F, Args...>::type>;
    ~ThreadPool();

private:
    // Need to keep track of threads so we can join them
    vector<thread> workers;
    // The task queue
    queue<function<void()>> tasks;

    // Synchronization
    mutex queue_mutex;
    condition_variable condition;
    bool stop;
};

#include "ThreadPool.tpp"

#endif /*THREADPOOL_H*/
