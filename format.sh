#!/bin/sh
tempfile=/tmp/clang_temp$$

find . -type f \( -name "*.cpp" -o -name "*.hpp" -o -name "*.c" -name "*." \) | grep -v clientGui| while read file;
do
echo $file
#cp "$file" "${file}~"

clang-format  "$file" > "$tempfile"

clang-modernize "$tempfile"
cp "$tempfile" "$file"
done
