#ifndef DIRECTORYITERATOR_HPP
#define DIRECTORYITERATOR_HPP

#include <sys/types.h>
#include <dirent.h>
#include <errno.h>
#include <exception>
namespace rightsfs {

class Directory {
public:
  Directory() : ent{nullptr} {}
  Directory(struct dirent *ent) : ent{ent} {}
  inline char *getName() { return ent->d_name; }
  inline operator bool() const { return ent != nullptr; }

protected:
  struct dirent *ent;
};

class DirectoryIterator {
public:
  class Exception : public std::exception {
  public:
    Exception(int err) : err{-err} {}
    operator int() const { return err; }

  private:
    int err;
  };

  DirectoryIterator(const char *directory)
      : directory{directory}, dir{opendir(directory)} {
    if (dir == nullptr) {
      throw Exception{errno};
    }
  }

  inline Directory getNext() { return Directory{readdir(dir)}; }
  ~DirectoryIterator() { closedir(dir); }

  const char *getDirectory() const { return directory; }
  const char *directory;
  DIR *dir = nullptr;
};
}

#endif // DIRECTORYITERATOR_HPP
