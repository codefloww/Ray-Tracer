#ifndef INTEGRATE_PARALLEL_QUEUE_THREAD_POOL_H
#define INTEGRATE_PARALLEL_QUEUE_THREAD_POOL_H
#include "threads_joiner.h"
#include "thread_safe_queue.h"
#include "future"
#include "task_wrapper.h"
#include "atomic"

class thread_pool {
private:
    std::atomic<bool> m_done;
    thread_safe_queue<task_wrapper> m_tasksQueue;
    std::vector<std::thread> m_threads;
    threads_joiner m_joiner;
    void worker_thread();
public:
    explicit thread_pool(unsigned int threads_number);
    ~thread_pool();

    template<typename Function, typename Args>
    auto submit(Function&& function, Args args) {
        using Return_type = typename std::invoke_result<Function, Args>::type;
        std::promise<Return_type> result_promise;
        std::future<Return_type> result(result_promise.get_future());
        task_wrapper new_task(function, args, result_promise);
        m_tasksQueue.enque(std::move(new_task));
        return result;
    }

    template<typename Function>
    auto submit(Function&& function) {
        using Return_type = typename std::invoke_result<Function>::type;
        std::promise<Return_type> result_promise;
        std::future<Return_type> result(result_promise.get_future());
        task_wrapper new_task(function, result_promise);
        m_tasksQueue.enque(std::move(new_task));
        return result;
    }

    inline void finish(){ m_done = true;}
};


#endif //INTEGRATE_PARALLEL_QUEUE_THREAD_POOL_H
