#include "../include/fifo_mutex.h"
void fifo_mutex::lock() {
    std::unique_lock<std::mutex> acquire(q_lock);
    std::condition_variable cv;
    q.push_back(&cv);
    q_empty.notify_one();
	cv.wait(acquire);
    }

void fifo_mutex::unlock() {
	std::unique_lock<std::mutex> acquire(q_lock);
	while (q.size() == 0)
		q_empty.wait(acquire);
	std::condition_variable *cv  = q.front();
	q.pop_front();
	cv->notify_one();
}

int fifo_mutex::size() {
	std::unique_lock<std::mutex> acquire(q_lock);
	return q.size();
}


