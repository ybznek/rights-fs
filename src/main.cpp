#include <iostream>
using namespace std;

#include "rightsfs/RightsFS.hpp"
#include <stdio.h>
#include <string.h>

rightsfs::RightsFS fs;
int main(int argc, char *argv[]) {
  fs.setDirectory("/home/data/projects/C++/rights-fs/testing");
  fs.setRightsFilename(".rightsFS");
  return fs.main(argc, argv);
}
