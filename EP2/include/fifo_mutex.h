#ifndef FIFO_MUTEX
#define FIFO_MUTEX
#include <deque>
#include <mutex>
#include <condition_variable>

class fifo_mutex{
    std::mutex q_lock;
    std::deque<std::condition_variable*> q;
    std::condition_variable q_empty;

public:
	void lock();
	void unlock();
	int size();
};
#endif //FIFO_MUTEXi
