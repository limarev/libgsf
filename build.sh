#!/bin/bash

# conan install . -vvv --output-folder=build-conan --build=missing --profile:build=default --profile:host=./conan/ios-arm64 -r=mycenter

preset=cmake-build-release
toolchain_path=""
rm -rf $preset
rm -rf install-tmp
cmake -DPLATFORM=OS64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=$toolchain_path -DCMAKE_INSTALL_PREFIX=install-tmp -S . -B $preset
cmake --build $preset
cmake --install $preset

preset_tmp=tmp/$preset
rm -rf $preset_tmp
current=$(pwd)
cmake -DCMAKE_BUILD_TYPE=Release -Dgsf_DIR=$current/install-tmp/lib/cmake/gsf -DCMAKE_TOOLCHAIN_FILE=$toolchain_path -S tmp -B $preset_tmp
cmake --build $preset_tmp
$preset_tmp/test.app/test createole asd.bin $preset_tmp