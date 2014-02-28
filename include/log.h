#if !defined(CPPGOODIES_LOG_H)
#define CPPGOODIES_LOG_H

#include <iostream>

namespace cppgoodies {
  static const char* InfoColor = "\033[01;34m";
  static const char* WarningColor = "\033[01;33m";
  static const char* FatalColor = "\033[01;31m";
  static const char* SourceColor = "\033[34m";
  static const char* EndColor = "\033[0m";

  class logger_base {
  public:
    template<typename T> logger_base  operator<<(T t) {
      return logger_base();
    }
  };

  class logger : public logger_base {
  private:
    bool _exit;
  public:
    logger(bool exit = false) : _exit(exit) {}
  
    ~logger() {
      std::cerr << EndColor << "\n";
      if(_exit) abort();
    }
  
    template<typename T> logger& operator<<(T t) {
      std::cerr << t;
      return *this;
    }
  };
}

#if defined(NDEBUG)
#  define LOG(color, exit) (cppgoodies::logger(exit) << color)
#  define INFO (cppgoodies::logger_base())
#else
#  define LOG(color, exit) cppgoodies::logger(exit) << cppgoodies::SourceColor << "[" << __FILE__ << ":" << __LINE__ << "] " << color
#  define INFO LOG(cppgoodies::InfoColor, false)
#endif

#define WARNING LOG(cppgoodies::WarningColor, false)
#define PREFER(cond) (cond) ? cppgoodies::logger_base() : WARNING

#define FATAL LOG(cppgoodies::FatalColor, true)
#define REQUIRE(cond) (cond) ? cppgoodies::logger_base() : FATAL

#endif