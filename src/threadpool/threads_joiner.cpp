#include "threadpool/threads_joiner.h"

threads_joiner::threads_joiner(std::vector<std::thread> &threads): threads_to_join(threads) {}
threads_joiner::~threads_joiner() {
    for(auto &thread: threads_to_join){
        if (thread.joinable()){
            thread.join();
        }
    }
}