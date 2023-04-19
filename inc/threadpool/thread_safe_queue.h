#ifndef INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H
#define INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H

#include <mutex>
#include <deque>
#include <condition_variable>

template<class T>
class thread_safe_queue {
private:
    std::deque<T> queue;
    std::mutex data_mutex;
    std::condition_variable queue_is_free;
public:
    thread_safe_queue() = default;
    ~thread_safe_queue() = default;
    thread_safe_queue(const thread_safe_queue&) = delete;
    thread_safe_queue& operator=(const thread_safe_queue&) = delete;

    size_t get_size() {
        std::unique_lock<std::mutex> guard{data_mutex};
        return queue.size();
    }

    T deque(){
        std::unique_lock<std::mutex> lck(data_mutex);
        while(queue.empty()){
            queue_is_free.wait(lck);
        }
        auto temp = std::move(queue.front());
        queue.pop_front();
        return temp;
    }

    bool try_lock_non_empty_queue(){
        if (data_mutex.try_lock()){
            if (!queue.empty()){
                return true;
            }
            data_mutex.unlock();
        }
        return false;
    }

    void enque(const T& temp){
        {
            std::lock_guard<std::mutex> lck(data_mutex);
            queue.push_back(temp);
        }
        queue_is_free.notify_one();
    }
    void enque(T&& temp){
        {
            std::lock_guard<std::mutex> lck(data_mutex);
            queue.push_back(std::move(temp));
        }
        queue_is_free.notify_one();
    }

    T careless_deque(){
        auto temp = std::move(queue.front());
        queue.pop_front();
        return temp;
    }

    void careless_enque(const T& temp){
        queue.push_back(temp);
    }

    void notifyConsumers(){
        queue_is_free.notify_all();
    }

    void lock_queue(){
        data_mutex.lock();
    }

    void unlock_queue(){
        data_mutex.unlock();
    }

    size_t careless_get_size(){
        return queue.size();
    }
};


#endif //INTEGRATE_PARALLEL_THREADSAFE_QUEUE_H
