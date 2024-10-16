#!/bin/bash

#####################################################################
#
#
#               compilar
#
#
#
#####################################################################


 #g++ -o app_st7789_drv main.cc st7789.cc -lbcm2835 

ALL=$1
CC=$2

if [[ $CC == "clang" ]]; then 
    cmake -DUSE_CLANG=ON -S . -B build/
    echo -e "\nUsando Clang como compilador\n"
fi



if [[ $ALL == "all" ]]; then
    rm -Rf build/
    cmake -S . -B build/
else
	make -j4 -C build/
fi

