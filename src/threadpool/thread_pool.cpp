#include "threadpool/thread_pool.h"

thread_pool::thread_pool(unsigned int threads_number): done{false}, tasksQueue{}, threads{}, joiner(threads){
    for (int i = 0; i < threads_number; i++){
        try{
            threads.emplace_back(&thread_pool::worker_thread, this);
        }
        catch (...){
            done=true;
            throw;
        }
    }
}

void thread_pool::worker_thread() {
    task_wrapper task;
    while (!done){
        try {
            if (tasksQueue.try_lock_non_empty_queue()){
                task = tasksQueue.careless_deque();
                tasksQueue.unlock_queue();
                task();
            }
            else{
                std::this_thread::yield();
            }
        }
        catch (...){
            done=true;
            throw;
        }
    }
}

thread_pool::~thread_pool() = default;

