
rem - clone code
rem git clone https://github.com/brinkqiang/exectime.git
rem pushd exectime
rem git submodule update --init --recursive

rmdir /S /Q build
mkdir build
pushd build
cmake -A x64 -DCMAKE_BUILD_TYPE=relwithdebinfo ..
cmake --build .  --config relwithdebinfo -- /m:%NUMBER_OF_PROCESSORS%

popd

rem pause