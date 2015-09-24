#ifndef RIGHTS_FS_HPP
#define RIGHTS_FS_HPP
#include "Fuse.hpp"
using namespace std;
namespace rightsfs {
class ZCache : public Fuse {
public:
  using Ctx = FuseCtx<ZCache>;

  ZCache();

  static inline Ctx getCtx() { return Ctx{fuse_get_context()}; }

  static inline ZCache *getFuse() { return ZCache::getCtx().getFuse(); }

  static int read(const char *path, char *buf, size_t size, off_t offset,
                  struct fuse_file_info *fi);

  static int open(const char *path, struct fuse_file_info *fi);

  static int release(const char *path, fuse_file_info *fi);

  static int access(const char *path, int amode);

//  static int opendir(const char* path, struct fuse_file_info* fi);

  static int write(const char *path, const char *buf, size_t size,off_t offset, struct fuse_file_info *fi);

  static int truncate(const char *path, off_t size);
  static int ftruncate(const char *path, off_t size,
          struct fuse_file_info *fi);


  static int readdir(const char *path, void *buf, fuse_fill_dir_t filler,
                     off_t offset, struct fuse_file_info *fi);

  static int getattr(const char *path, struct stat *stbuf);
};
}
#endif // RIGHTS_FUSE_HPP
