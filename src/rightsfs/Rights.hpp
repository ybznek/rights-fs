#ifndef RIGHTS_HPP
#define RIGHTS_HPP
#include <map>
#include "common/Mem.hpp"
#include "common/Str.hpp"
#include "SimpleStr.hpp"
#include "Path.hpp"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <vector>
using namespace std;
namespace rightsfs {

struct RightsOpt {
  uid_t uid;
  gid_t gid;
  mode_t mode;
};

#if __BYTE_ORDER != __LITTLE_ENDIAN
#error "Unsupported platform"
#endif

class RightsInstance {
public:
  RightsInstance(SimpleStr *key);

  void chmod(const char *filename, mode_t mode) {
    SimpleStr s{filename, false};
    try {
      printf("aa\n");
      opts[&s].gid = mode;
      printf("uz je\n");
    } catch (std::out_of_range &) {
      printf("novy\n");
      RightsOpt opt{};
      opt.mode = mode;
      opts.insert(
          std::pair<SimpleStr *, RightsOpt>(new SimpleStr{filename}, opt));
    }
    dirty = true;
    sync();
  }
  void sync();
  ~RightsInstance();

protected:
  map<SimpleStr *, RightsOpt> opts;
  bool dirty = false;
  SimpleStr *key;
  int fd;
};

class Rights {
public:
  Rights();
  RightsInstance &getInstance(const char *rightsPath);
  void sync();

protected:
  map<SimpleStr *, RightsInstance *> rights;
};
}
#endif // RIGHTS_HPP
