#!/bin/sh
dir=./moje

killall rightsfs
umount $dir
rmdir $dir

mkdir $dir
/home/data/projects/C++/rights-fs/build/rightsfs $dir
ls -la $dir
cat $dir/xfce-image-pkgs.txt 
cp $dir/xfce-image-pkgs.txt /tmp/xfce
cat /tmp/xfce
rm /tmp/xfce

#killall rightsfs
#umount $dir
#rmdir $dir
