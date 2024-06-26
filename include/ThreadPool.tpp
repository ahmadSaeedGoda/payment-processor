#ifndef THREADPOOL_TPP
#define THREADPOOL_TPP

// Add new work item to the pool
template <class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&...args) -> future<typename invoke_result<F, Args...>::type>
{
    using return_type = typename invoke_result<F, Args...>::type;

    auto task = make_shared<packaged_task<return_type()>>(
        bind(forward<F>(f), forward<Args>(args)...));

    future<return_type> res = task->get_future();
    {
        unique_lock<mutex> lock(queue_mutex);

        if (stop)
            throw runtime_error("enqueue on stopped ThreadPool");

        tasks.emplace([task]()
                      { (*task)(); });
    }
    condition.notify_one();
    return res;
}

#endif // THREADPOOL_TPP
