#!/bin/bash
clear
rm -f build
mkdir build
cd build
conan install .. --build=missing
