#ifndef ORDERED_MUTEX
#define ORDERED_MUTEX
#include <mutex>
#include <condition_variable>
#include <queue>

class ordered_mutex {
    std::queue<std::condition_variable>  cvar;
    std::mutex                           cvar_lock;
    bool                                 locked;
	public:
    ordered_mutex() : locked(false) {};
    void lock();
    void unlock(); 
};
#endif
