#include "threadpool/thread_pool.h"

thread_pool::thread_pool(unsigned int threads_number): m_done{false}, m_tasksQueue{}, m_threads{}, m_joiner(m_threads){
    for (int i = 0; i < threads_number; i++){
        try{
            m_threads.emplace_back(&thread_pool::worker_thread, this);
        }
        catch (...){
            m_done=true;
            throw;
        }
    }
}

void thread_pool::worker_thread() {
    task_wrapper task;
    while (!m_done){
        try {
            if (m_tasksQueue.try_lock_non_empty_queue()){
                task = m_tasksQueue.careless_deque();
                m_tasksQueue.unlock_queue();
                task();
            }
            else{
                std::this_thread::yield();
            }
        }
        catch (...){
            m_done=true;
            throw;
        }
    }
}

thread_pool::~thread_pool() = default;

