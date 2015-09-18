#ifndef MEM_HPP
#define MEM_HPP
#include <string.h>
namespace zcachefs {
class Mem {
public:
  template <typename T> static inline void clear(T *var) {
    memset(var, 0, sizeof(T));
  }
};
}
#endif // MEM_HPP
