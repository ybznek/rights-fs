#ifndef MEM_HPP
#define MEM_HPP
#include <string.h>
#include <unistd.h>

namespace rightsfs {
class Mem {
public:
  template <typename T> static inline void clear(T *var) {
    memset(var, 0, sizeof(T));
  }

  template <typename T> static inline bool write(int fd, const T *t) {
    auto size = sizeof(T);
    return ::write(fd, t, size) == size;
  }
  template <typename T> static inline bool read(int fd, T *t) {
    auto size = sizeof(T);
    return ::read(fd, t, size) == size;
  }

  static void cpy(void *dst, const void *src, size_t size) {
    memcpy(dst, src, size);
  }
};
}
#endif // MEM_HPP
