#ifndef FUSEERRORS_HPP
#define FUSEERRORS_HPP
#include <errno.h>
namespace rightsfs {
class FuseErrors {
public:
  enum {
    OK = 0,
    PERM = -EPERM,     /* Operation not permitted */
    NOENT = -ENOENT,   /* No such file or directory */
    SRCH = -ESRCH,     /* No such process */
    INTR = -EINTR,     /* Interrupted system call */
    IO = -EIO,         /* I/O error */
    NXIO = -ENXIO,     /* No such device or address */
    TOO_BIG = -E2BIG,  /* Argument list too long */
    NOEXEC = -ENOEXEC, /* Exec format error */
    BADF = -EBADF,     /* Bad file number */
    CHILD = -ECHILD,   /* No child processes */
    AGAIN = -EAGAIN,   /* Try again */
    NOMEM = -ENOMEM,   /* Out of memory */
    ACCES = -EACCES,   /* Permission denied */
    FAULT = -EFAULT,   /* Bad address */
    NOTBLK = -ENOTBLK, /* Block device required */
    BUSY = -EBUSY,     /* Device or resource busy */
    EXIST = -EEXIST,   /* File exists */
    XDEV = -EXDEV,     /* Cross-device link */
    NODEV = -ENODEV,   /* No such device */
    NOTDIR = -ENOTDIR, /* Not a directory */
    ISDIR = -EISDIR,   /* Is a directory */
    INVAL = -EINVAL,   /* Invalid argument */
    NFILE = -ENFILE,   /* File table overflow */
    MFILE = -EMFILE,   /* Too many open files */
    NOTTY = -ENOTTY,   /* Not a typewriter */
    TXTBSY = -ETXTBSY, /* Text file busy */
    FBIG = -EFBIG,     /* File too large */
    NOSPC = -ENOSPC,   /* No space left on device */
    SPIPE = -ESPIPE,   /* Illegal seek */
    ROFS = -EROFS,     /* Read-only file system */
    MLINK = -EMLINK,   /* Too many links */
    PIPE = -EPIPE,     /* Broken pipe */
    DOM = -EDOM,       /* Math argument out of domain of func */
    RANGE = -ERANGE,   /* Math result not representable */
  };

private:
  FuseErrors();
};
}

#endif // FUSEERRORS_HPP
