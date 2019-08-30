#/bin/sh
clang++ -O2 -g -fsanitize=address -fno-omit-frame-pointer -I'/home/kuro/Desktop/OpenRTM-aist/src/lib/coil/common' -I'/home/kuro/Desktop/OpenRTM-aist/src/lib/coil/posix/'  /home/kuro/Desktop/OpenRTM-aist/src/lib/coil/common/coil/stringutil.cpp ${1} && ./a.out
