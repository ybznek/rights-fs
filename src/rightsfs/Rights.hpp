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
#include <sys/stat.h>
#include <mutex>
using namespace std;
namespace rightsfs {

struct RightsOpt {
  uid_t uid =0;
  gid_t gid =0;
  mode_t mode =0;

  bool _align;

  bool uid_valid = false;
  bool gid_valid = false;
  bool mode_valid = false;
};

#if __BYTE_ORDER != __LITTLE_ENDIAN
#error "Unsupported platform"
#endif

class RightsInstance {
public:
  RightsInstance(SimpleStr *key);

  struct stat getFinalRights(const char* filename, const struct stat& originalStats){
        struct stat finalStats=originalStats;
        SimpleStr s{filename, false};
        auto it = opts.find(&s);
        if (it == opts.end()){
            printf("nemicham \n");
           return finalStats;
        }
        printf("micham\n");
        RightsOpt& opt= it->second;
        if (opt.gid_valid){
            printf("gid\n");
            finalStats.st_gid = opt.gid;
        }
        if (opt.uid_valid){
            printf("uid\n");
            finalStats.st_uid = opt.uid;
        }
        if (opt.mode_valid){
            printf("mode\n");
            finalStats.st_mode = opt.mode;
        }
        return finalStats;
  }


  void chmod(const char *filename, mode_t mode) {
    SimpleStr* str= new SimpleStr{filename};
    RightsOpt& item= opts[str];
    item.mode = mode;
    item.mode_valid = true;
    dirty = true;
    sync();
  }
  void sync();
  ~RightsInstance();

protected:
  map<SimpleStrRef, RightsOpt> opts;
  bool dirty = false;
  SimpleStr *key;
  int fd;
};

class Rights {
public:
  Rights();
  RightsInstance *getInstance(const char *rightsPath);
  void sync();

protected:
  map<SimpleStrRef, RightsInstance *> rights;
  std::mutex rightsMutex;
};
}
#endif // RIGHTS_HPP
