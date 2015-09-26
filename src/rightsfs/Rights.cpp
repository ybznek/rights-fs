#include "Rights.hpp"

#include <sys/param.h>

rightsfs::RightsInstance::RightsInstance(rightsfs::SimpleStr *key) : key{key} {

  fd = ::open(key->to_cstr(), O_CREAT | O_RDWR);
  printf("fd %s:%d\n", key->to_cstr(), fd);
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
    SimpleStr *str = new SimpleStr{size};
    if (!Str::read(fd, str->raw(), size)) {
      break;
    }

    opts.emplace(std::pair<SimpleStr *, RightsOpt>(str, opt));
  }
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
  static_assert(sizeof(RightsOpt) == 3 * 4, "Should use 32bit rights");
}

rightsfs::RightsInstance &
rightsfs::Rights::getInstance(const char *rightsPath) {
  SimpleStr s{rightsPath, false};
  try {
    return *(rights[&s]);
  } catch (std::out_of_range &) {
    SimpleStr *key = new SimpleStr{rightsPath};
    RightsInstance *ins = new RightsInstance{key};
    rights.emplace(std::pair<SimpleStr *, RightsInstance *>(key, ins));
    return *ins;
  }
}

void rightsfs::Rights::sync() {
  for (auto &it : rights) {
    it.second->sync();
  }
}
