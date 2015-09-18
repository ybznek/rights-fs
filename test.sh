#!/bin/sh
dir=./moje
mkdir $dir
/home/data/projects/C++/rights-fs/build/rightsfs $dir
ls -la $dir
cat $dir/xfce-image-pkgs.txt 
killall rightsfs
umount $dir
rmdir $dir
