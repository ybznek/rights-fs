#include "Rights.hpp"

#include <sys/param.h>
rightsfs::RightsInstance::RightsInstance(rightsfs::SimpleStr *key) : key{key} {


   fd = ::open(key->to_cstr(), O_CREAT | O_RDWR, 0666);
  printf("rights fd %s:%d\n", key->to_cstr(), fd);

  while (true) {
    RightsOpt opt;
    if (!Mem::read<RightsOpt>(fd, &opt)) {
      break;
    }
    size_t size;
    if (!Mem::read<size_t>(fd, &size)) {
      break;
    }
    if (size >= PATH_MAX) {
      break;
    }
    SimpleStr *str = new SimpleStr{size+1};
    if (!Str::read(fd, str->raw(), size)) {
      break;
    }

    opts.insert(std::pair<SimpleStrRef, RightsOpt>(str, opt));
  }
  printf("loaded\n");
}

void rightsfs::RightsInstance::sync() {
  if (!dirty) {
    return;
  }
  printf("synced\n");
  //    ::ftruncate(fd, 0);
  for (auto &it : opts) {
    printf("iter\n");
    const SimpleStr *str = it.first;
    Mem::write<RightsOpt>(fd, &(it.second));
    size_t len = str->len();
    Mem::write<size_t>(fd, &(len));
    ::write(fd, str->to_cstr(), len);
  }

  ::fsync(fd);
  dirty = false;
}

rightsfs::RightsInstance::~RightsInstance() {
  sync();
  ::close(fd);
}

rightsfs::Rights::Rights() {
  static_assert(sizeof(RightsOpt) == (3 * 4 + 3 +1), "Should use 32bit rights structures");
}

rightsfs::RightsInstance *
rightsfs::Rights::getInstance(const char *rightsPath) {
    std::lock_guard<std::mutex> g(rightsMutex);
    printf("rightsPath: %s\n",rightsPath);
  SimpleStr s{rightsPath, false};
        auto it= rights.find(&s);

      if (it == rights.end()){
          SimpleStr *key = new SimpleStr{rightsPath};
          RightsInstance *ins = new RightsInstance{key};
          rights.insert(std::pair<SimpleStrRef, RightsInstance *>(key, ins));
          return ins;
      }else{
                return it->second;
      }
}

void rightsfs::Rights::sync() {
  for (auto &it : rights) {
    it.second->sync();
  }
}
