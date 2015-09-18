#include "ZCache.hpp"
#include "FuseErrors.hpp"
#include <iostream>
#include "common/Str.hpp"
#include "common/Mem.hpp"
#define FS(var) ZCache &var = *(ZCache::getFuse())
#define IMPL(func) operations.func = ZCache::func
namespace zcachefs {
using E = FuseErrors;

ZCache::ZCache() {
  IMPL(read);
  IMPL(open);
  IMPL(readdir);
  IMPL(getattr);
}

int ZCache::read(const char *path, char *buf, size_t size, off_t offset,
                 fuse_file_info *fi) {
  FS(f);

  return E::NOENT;
}

int ZCache::open(const char *path, fuse_file_info *fi) { return E::OK; }

int ZCache::readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                    off_t offset, fuse_file_info *fi) {

  filler(buf, ".", nullptr, 0);
  filler(buf, "..", nullptr, 0);
  filler(buf, "hahaha", nullptr, 0);
  filler(buf, "te", nullptr, 0);
  return E::OK;
}

int ZCache::getattr(const char *path, struct stat *stbuf) {
  Mem::clear<struct stat>(stbuf);
  if (Str::equals(path, "/") || Str::equals(path, "/hahaha")) {
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = 2;
  } else if (Str::equals(path, "/te")) {
    stbuf->st_mode = S_IFREG | 0755;
  }
  return E::OK;
}
}
