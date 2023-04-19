#ifndef INTEGRATE_PARALLEL_QUEUE_THREADS_JOINER_H
#define INTEGRATE_PARALLEL_QUEUE_THREADS_JOINER_H
#include <vector>
#include <thread>

class threads_joiner {
private:
    std::vector<std::thread> &m_threads_to_join;
public:
    explicit threads_joiner(std::vector<std::thread> &threads);
    ~threads_joiner();
};


#endif //INTEGRATE_PARALLEL_QUEUE_THREADS_JOINER_H
