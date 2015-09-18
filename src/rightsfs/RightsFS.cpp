#include "RightsFS.hpp"
#include "FuseErrors.hpp"
#include <iostream>
#include "FileStat.hpp"
#include "common/Str.hpp"
#include "common/Mem.hpp"
#include "DirectoryIterator.hpp"
#include <unistd.h>

#define FS(var) ZCache &var = *(ZCache::getFuse())
#define IMPL(func) operations.func = ZCache::func
namespace rightsfs {
using E = FuseErrors;

ZCache::ZCache() {
  IMPL(read);
  IMPL(open);
  IMPL(readdir);
  IMPL(getattr);
}

int ZCache::read(const char *path, char *buf, size_t size, off_t offset,
                 fuse_file_info *fi) {
    int fd;
    int res;
    (void) fi;
    fd = open(path, O_RDONLY);
    if (fd == -1)
            return -errno;
    res = pread(fd, buf, size, offset);
    if (res == -1)
            res = -errno;
    close(fd);
    return res;
}

int ZCache::open(const char *path, fuse_file_info *fi) {
    int res;
    res = ::open(path, fi->flags);
    if (res == -1)
            return -errno;
    close(res);
    return 0;
}

int ZCache::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                    off_t offset, fuse_file_info *fi) {
  try {
    DirectoryIterator it{path};

    for (Directory dir; dir = it.getNext();) {
      FileStat stat{path, dir.getName()};
      filler(buf, dir.getName(), stat, offset);
    }

  } catch (DirectoryIterator::Exception &ex) {
    return ex;
  }
  return E::OK;
}

int ZCache::getattr(const char *path, struct stat *stbuf) {
  FileStat stat{path};
  *stbuf = *stat;
  return stat;
}
}
