#!/bin/bash

git submodule init
git submodule update --remote --recursive
mkdir -p dev/MinGfx/build
cd dev/MinGfx/build

if [ -z "$1" ]
then
	cmake .. -DCMAKE_INSTALL_PREFIX=../../.. -DAUTOBUILD_NANOGUI=ON
else
	cmake .. -G "$1" -DCMAKE_INSTALL_PREFIX=../../.. -DAUTOBUILD_NANOGUI=ON
fi
cmake --build . --target install
