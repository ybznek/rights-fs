#ifndef ZCACHEFSFUSE_HPP
#define ZCACHEFSFUSE_HPP
#include "Fuse.hpp"
namespace zcachefs {
class ZCache : public Fuse {
public:
  using Ctx = FuseCtx<ZCache>;

  ZCache();

  static inline Ctx getCtx() { return Ctx{fuse_get_context()}; }

  static inline ZCache *getFuse() { return ZCache::getCtx().getFuse(); }

  static int read(const char *path, char *buf, size_t size, off_t offset,
                  struct fuse_file_info *fi);

  static int open(const char *path, struct fuse_file_info *fi);

  static int readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                     off_t offset, struct fuse_file_info *fi);

  static int getattr(const char *path, struct stat *stbuf);
};
}
#endif // ZCACHEFSFUSE_HPP
