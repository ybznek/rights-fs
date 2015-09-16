#!/bin/sh
mkdir moje
/home/data/projects/C++/zcache/build/zcachefs ./moje
ls -la ./moje
killall zcachefs

rmdir ./moje
