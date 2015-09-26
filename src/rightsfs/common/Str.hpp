#ifndef STR_HPP
#define STR_HPP
#include <string.h>
#include <unistd.h>
namespace rightsfs {

class Str {
public:
  static inline char *cpy(char *dst, const char *src) {
    return strcpy(dst, src);
  }

  static bool read(int fd, char *str, size_t size) {
    size_t read = ::read(fd, str, size);
    if (read == size) {
      str[read] = '\0';
      return true;
    } else {
      return false;
    }
  }

  static inline bool equals(const char *s1, const char *s2) {
    return (strcmp(s1, s2) == 0);
  }
  static inline int cmp(const char *s1, const char *s2) {
    return strcmp(s1, s2);
  }

  static inline size_t len(const char *str) { return strlen(str); }
};
}
#endif // STR_HPP
