#ifndef INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H
#define INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template<class T>
class thread_safe_queue {
private:
    std::deque<T> m_queue;
    std::mutex m_data_mutex;
    std::condition_variable m_queue_is_free;
public:
    thread_safe_queue() = default;
    ~thread_safe_queue() = default;
    thread_safe_queue(const thread_safe_queue&) = delete;
    thread_safe_queue& operator=(const thread_safe_queue&) = delete;

    size_t get_size() {
        std::unique_lock<std::mutex> guard{m_data_mutex};
        return m_queue.size();
    }

    T deque(){
        std::unique_lock<std::mutex> lck(m_data_mutex);
        while(m_queue.empty()){
            m_queue_is_free.wait(lck);
        }
        auto temp = std::move(m_queue.front());
        m_queue.pop_front();
        return temp;
    }

    bool try_lock_non_empty_queue(){
        if (m_data_mutex.try_lock()){
            if (!m_queue.empty()){
                return true;
            }
            m_data_mutex.unlock();
        }
        return false;
    }

    void enque(const T& temp){
        {
            std::lock_guard<std::mutex> lck(m_data_mutex);
            m_queue.push_back(temp);
        }
        m_queue_is_free.notify_one();
    }
    void enque(T&& temp){
        {
            std::lock_guard<std::mutex> lck(m_data_mutex);
            m_queue.push_back(std::move(temp));
        }
        m_queue_is_free.notify_one();
    }

    T careless_deque(){
        auto temp = std::move(m_queue.front());
        m_queue.pop_front();
        return temp;
    }

    void careless_enque(const T& temp){
        m_queue.push_back(temp);
    }

    void notifyConsumers(){
        m_queue_is_free.notify_all();
    }

    void lock_queue(){
        m_data_mutex.lock();
    }

    void unlock_queue(){
        m_data_mutex.unlock();
    }

    size_t careless_get_size(){
        return m_queue.size();
    }
};


#endif //INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H
