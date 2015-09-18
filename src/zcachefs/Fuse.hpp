#ifndef FUSE_HPP
#define FUSE_HPP
#include <fuse.h>
#include <errno.h>
#include <fcntl.h>
#include "FuseCtx.hpp"
namespace zcachefs {
class Fuse {
public:
  int inline main(int argc, char *argv[]) {
    return fuse_main(argc, argv, &operations, this);
  }

  static inline struct fuse_context *getFuseContext() {
    return fuse_get_context();
  }

protected:
  struct fuse_operations operations = {};
};
}
#endif // FUSE_HPP
