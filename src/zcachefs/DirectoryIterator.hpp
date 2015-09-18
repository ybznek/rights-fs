#ifndef DIRECTORYITERATOR_HPP
#define DIRECTORYITERATOR_HPP

#include <sys/types.h>
#include <dirent.h>

namespace zcachefs{
class DirectoryIterator
{
public:
    DirectoryIterator(const char* directory):directory{directory}{
    }

    bool open(){
        dir = opendir(directory);
    }
    ~DirectoryIterator(){
        closedir(dir);
    }
    const char* directory;
    DIR* dir= nullptr;
};
}

#endif // DIRECTORYITERATOR_HPP
