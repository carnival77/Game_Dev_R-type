#!/bin/bash
clear
mkdir build
cd build
conan install .. --build=missing
