#ifndef SIMPLESTR_HPP
#define SIMPLESTR_HPP
#include "common/Str.hpp"
#include "common/Mem.hpp"
#include <string>
namespace rightsfs {
class SimpleStr {
public:
  SimpleStr(SimpleStr &&str) {
    std::swap(this->cstr, str.cstr);
    this->length = str.length;
  }

  SimpleStr(size_t len) : length{len} { cstr = new char[length]; }

  SimpleStr(const char *str, bool owned = true) : owned{owned} {
    if (!owned) {
      this->cstr = const_cast<char *>(str);
    } else {
      length = strlen(str);
      cstr = new char[length];
      Mem::cpy(this->cstr, str, length + 1);
    }
  }

  bool operator<(const SimpleStr &str) {
    return (Str::cmp(cstr, str.cstr) < 0);
  }

  operator const char *() const { return cstr; }

  const char *to_cstr() const { return cstr; }

  char *raw() { return cstr; }
  size_t len() const { return length; }

  ~SimpleStr() {
    if (owned) {
      delete[] cstr;
    }
  }

  SimpleStr() {}

protected:
  char *cstr = nullptr;
  size_t length = 0;
  bool owned = true;
};
}
#endif // SIMPLESTR_HPP
