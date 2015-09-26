#ifndef SIMPLESTR_HPP
#define SIMPLESTR_HPP
#include "common/Str.hpp"
#include "common/Mem.hpp"
#include <string>
namespace rightsfs {


class SimpleStr {
    friend class SimpleStrRef;
public:
  SimpleStr(size_t len) : length{len} { cstr = new char[length]; }

  SimpleStr(const char *str, bool owned = true) : owned{owned} {
    if (!owned) {
        cstr = const_cast<char *>(str);
    } else {
        copyStrIntoThis(str);
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
  void copyStrIntoThis(const char* str){
      length = strlen(str);
      cstr = new char[length+1];
      Mem::cpy(cstr, str, length + 1);
  }
  char *cstr = nullptr;
  size_t length = 0;
  bool owned = true;
};




class SimpleStrRef{
public:
    SimpleStrRef(SimpleStr* str):str{str}{

    }



    operator SimpleStr*(){
        return str;
    }

    operator const SimpleStr*()const{
        return str;
    }

    bool operator<(const SimpleStrRef &ref) const{
        return *str  < *(ref.str);
    }
protected:
    SimpleStr* str;
};

}




#endif // SIMPLESTR_HPP
