#ifndef STR_HPP
#define STR_HPP
#include <string.h>
namespace zcachefs {

class Str {
public:
  Str(char *cstr) : cstr{cstr} {}

  inline int cmp(const char *cstr) const { return Str::cmp(this->cstr, cstr); }

  inline bool equals(const char *cstr) { return Str::equals(this->cstr, cstr); }

  static inline bool equals(const char *s1, const char *s2) {
    return (strcmp(s1, s2) == 0);
  }
  static inline int cmp(const char *s1, const char *s2) {
    return strcmp(s1, s2);
  }

  inline operator char *() { return cstr; }

protected:
  char *cstr;
};
}
#endif // STR_HPP
