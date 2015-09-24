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
  IMPL(write);
  IMPL(open);
  IMPL(access);
  IMPL(release);
  IMPL(readdir);
  IMPL(getattr);
  IMPL(truncate);
  IMPL(ftruncate);
}

int ZCache::read(const char *path, char *buf, size_t size, off_t offset,
                 fuse_file_info *fi) {
    int fd = fi->fh;
    return ::pread(fd, buf, size, offset);
}

int ZCache::open(const char *path, fuse_file_info *fi) {
    int ret = ::open(path, fi->flags);
    if (ret== -1)
    {
        return -1;
    } else {
            fi->fh = ret;
            return 0;
    }
}

int ZCache::release(const char *path, fuse_file_info *fi) {
    return ::close(fi->fh);
}

int ZCache::access(const char *path, int amode){
    return  -::access(path,amode);
}

int ZCache::write(const char *path, const char *buf, size_t size,
       off_t offset, struct fuse_file_info *fi){
    return ::pwrite(fi->fh,buf,size,offset);
}


int ZCache::truncate(const char *path, off_t size){
    return ::truncate(path,size);
}

int ZCache::ftruncate(const char *path, off_t size, fuse_file_info *fi){
        return ::ftruncate(fi->fh,size);
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
