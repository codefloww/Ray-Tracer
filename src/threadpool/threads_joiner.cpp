#include "threadpool/threads_joiner.h"

threads_joiner::threads_joiner(std::vector<std::thread> &threads): m_threads_to_join(threads) {}
threads_joiner::~threads_joiner() {
    for(auto &thread: m_threads_to_join){
        if (thread.joinable()){
            thread.join();
        }
    }
}