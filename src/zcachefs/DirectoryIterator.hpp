#ifndef DIRECTORYITERATOR_HPP
#define DIRECTORYITERATOR_HPP

#include <sys/types.h>
#include <dirent.h>

namespace zcachefs{
class DirectoryIterator
{
public:
    DirectoryIterator(const char* directory){
        dir = opendir(directory);
    }

    ~DirectoryIterator(){
        closedir(dir);
    }
    DIR* dir;
};
}

#endif // DIRECTORYITERATOR_HPP
