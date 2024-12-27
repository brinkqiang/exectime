#!/bin/bash

# - install depends tools
# yum -y install git
# yum -y install gcc gcc-c++ autoconf libtool automake make
#

# pushd thirdparty/depends_path
# libtoolize && aclocal && autoheader && autoconf && automake --add-missing
# sh configure
# popd

rm -rf build
mkdir -p build
cd build

cmake -DCMAKE_BUILD_TYPE=relwithdebinfo -DCMAKE_INSTALL_PREFIX=/opt ..
cmake --build . --config relwithdebinfo

cd ..
# popd

# echo continue && read -n 1
