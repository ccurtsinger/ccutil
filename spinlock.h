#if !defined(CCUTIL_SPINLOCK_H)
#define CCUTIL_SPINLOCK_H

#include <atomic>

class spinlock {
public:
  inline void lock() {
    while(_flag.test_and_set()) {
      __asm__ __volatile__ ("pause");
    }
  }
  
  inline bool trylock() {
    return !_flag.test_and_set();
  }
  
  inline void unlock() {
    _flag.clear();
  }
  
private:
  std::atomic_flag _flag = ATOMIC_FLAG_INIT;
};

#endif
