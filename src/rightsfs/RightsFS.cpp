#include "RightsFS.hpp"
#include "FuseErrors.hpp"
#include <iostream>
#include "FileStat.hpp"
#include "common/Str.hpp"
#include "common/Mem.hpp"
#include "DirectoryIterator.hpp"
#include <unistd.h>
#include <string.h>
#define FS(var) RightsFS &var = *(RightsFS::getFuse())
#define IMPL(func) operations.func = RightsFS::func

extern rightsfs::RightsFS fs;

namespace rightsfs {
using E = FuseErrors;

RightsFS::RightsFS() {

  IMPL(read);
  IMPL(write);
  IMPL(open);
  IMPL(chmod);
  IMPL(access);
  IMPL(release);
  IMPL(readdir);
  IMPL(getattr);
  IMPL(truncate);
  IMPL(ftruncate);
}

void RightsFS::setRightsFilename(const char *filename) {
  this->rightsFilename = filename;
}

void RightsFS::setDirectory(const char *directory) {
  path.setBaseDir(directory);
}

int RightsFS::read(const char *path, char *buf, size_t size, off_t offset,
                   fuse_file_info *fi) {

  Path::PathPair pair = fs.path.getRealPathPair(path);
  printf("p: %s\n", pair.getFilename());
  int fd = fi->fh;
  return ::pread(fd, buf, size, offset);
}

int RightsFS::open(const char *path, fuse_file_info *fi) {
  printf("path:%s\n", path);
  const char *realPath = fs.path.getRealPath(path);
  int ret = ::open(realPath, fi->flags);
  if (ret == -1) {
    return -1;
  } else {
    fi->fh = ret;
    return 0;
  }
}

int RightsFS::release(const char *path, fuse_file_info *fi) {
  return ::close(fi->fh);
}

int RightsFS::access(const char *path, int amode) {
  Path::PathPair pair = fs.path.getRealPathPair(path);
  printf("filename %s\n", pair.getFilename());
  if (::access(pair.getPath(), amode) < 0) {
    return -1;
  } else {
    return 0;
  }
}

int RightsFS::write(const char *path, const char *buf, size_t size,
                    off_t offset, struct fuse_file_info *fi) {
  return ::pwrite(fi->fh, buf, size, offset);
}

int RightsFS::truncate(const char *path, off_t size) {
  const char *realPath = fs.path.getRealPath(path);
  return ::truncate(realPath, size);
}

int RightsFS::ftruncate(const char *path, off_t size, fuse_file_info *fi) {
  return ::ftruncate(fi->fh, size);
}

int RightsFS::chmod(const char *path, mode_t mode) {
  printf("chmod called\n");
  Path::PathPair pair = fs.path.getRealPathPair(path);
  RightsInstance *ins = fs.getRights(pair);
  ins->chmod(pair.getFilename(), mode);
  return 0;
}

int RightsFS::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                      off_t offset, fuse_file_info *fi) {
  const char *realPath = fs.path.getRealPath(path);
  try {
    DirectoryIterator it{realPath};

    for (Directory dir; dir = it.getNext();) {
      FileStat stat{realPath, dir.getName()};
      filler(buf, dir.getName(), stat, offset);
    }

  } catch (DirectoryIterator::Exception &ex) {
    return ex;
  }
  return E::OK;
}

int RightsFS::getattr(const char *path, struct stat *stbuf) {
  Path::PathPair pair = fs.path.getRealPathPair(path);
  const char *filename = pair.getFilename();
  if (Str::equals(fs.rightsFilename, filename)) {
    return E::NOENT;
  }

  RightsInstance* ins = fs.getRights(pair);
  pair.getRightsPath(fs.rightsFilename, fs.rightFsPath);
//  RightsInstance *r = fs.rights.getInstance(fs.rightFsPath);
  FileStat stat{pair.getPath()};
  *stbuf = ins->getFinalRights(pair.getFilename(),*stat);
  return stat;
}

RightsInstance *RightsFS::getRights(Path::PathPair &pair) {
  pair.getRightsPath(rightsFilename, rightFsPath);
  return rights.getInstance(rightFsPath);
}
}
