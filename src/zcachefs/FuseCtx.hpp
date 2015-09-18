#ifndef FUSECTX_HPP
#define FUSECTX_HPP
#include <fuse.h>
namespace zcachefs {
class Fuse;
template <class CLS> class FuseCtx {
public:
  inline FuseCtx(struct fuse_context *ctx) : ctx{ctx} {}
  inline CLS *getFuse() { return static_cast<CLS *>(ctx->private_data); }

protected:
  struct fuse_context *ctx = {};
};
}

#endif // FUSECTX_HPP
