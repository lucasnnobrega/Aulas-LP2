#ifndef __EP1HELPERS__
#define __EP1HELPERS__
#include <atomic>
#include <mutex>
void lock(std::atomic_flag&);
void unlock(std::atomic_flag&);
#endif//HELP










