#ifndef FUSECTX_HPP
#define FUSECTX_HPP
#include <fuse.h>
namespace rightsfs {
class Fuse;
template <class CLS> class FuseCtx {
public:
  inline FuseCtx(struct fuse_context *ctx) : ctx{ctx} {}

protected:
  struct fuse_context *ctx = {};
};
}

#endif // FUSECTX_HPP
