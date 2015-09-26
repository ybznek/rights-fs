#ifndef PATH_HPP
#define PATH_HPP
#include <string.h>
#include <limits.h>
#include <stdlib.h>

#include "common/Str.hpp"
#include "common/Mem.hpp"
namespace rightsfs {
class Path {
public:
  using Buffer = char[PATH_MAX];
  struct PathPair {
    PathPair(char *path, size_t index) : path{path}, index{index} {}
    const char *getFilename() { return &(path[index]); }

    const char *getPath() { return path; }

    inline void getRightsPath(const char *rightsFilename, char *dst) {
      // todo check file
      Mem::cpy(dst, path, index - 1);
      Str::cpy(&(dst[index]), rightsFilename);
    }

  protected:
    const char *path;
    size_t index;
  };
  void setBaseDir(const char *baseDir) {
    ::realpath(baseDir, this->directory);
    directoryEnd = strlen(this->directory);
  }

  char *getRealPath(const char *relativeDir) {
    // todo check max length size
    Str::cpy(&(directory[directoryEnd]), relativeDir);
    return this->directory;
  }

  PathPair getRealPathPair(const char *relativeDir) {
    size_t len = Str::len(relativeDir);
    Mem::cpy(&(directory[directoryEnd]), relativeDir, len + 1);
    size_t index = directoryEnd + len - 1;
    for (; directory[index] != '/'; index--) {
      ;
    }
    ++index;
    return PathPair{this->directory, index};
  }

protected:
  Buffer directory;
  size_t directoryEnd;
};
}

#endif // PATH_HPP
