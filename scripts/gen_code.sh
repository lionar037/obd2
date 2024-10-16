#!/bin/bash

#ADD_FILES=$(find . -type f -name "main.cc")
ADD_FILES+=" $(find include/ -type f -name "*.hpp") "
ADD_FILES+=" $(find src/ -type f -name "*.cpp") "
ADD_FILES+=" $(find . -type f -name "CMakeLists.txt") "

cat $ADD_FILES > codeAlls.cpp