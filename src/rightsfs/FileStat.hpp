#ifndef FILESTAT_HPP
#define FILESTAT_HPP
#include <exception>
#include <sys/stat.h>
#include <string>
class FileStat {
public:
  FileStat(const char *dir, const char *name) {
    std::string path{dir};
    path += '/';
    path += name;
    getStat(path.c_str());
  }
  FileStat(const char *path) { getStat(path); }
  operator const struct stat *() const { return &buf; }
  operator int() const { return ret; }

protected:
  void getStat(const char *path) { ret = stat(path, &buf); }
  struct stat buf;
  int ret;
};

#endif // FILESTAT_HPP
