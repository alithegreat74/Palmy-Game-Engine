@echo off
pushd %~dp0\..\
CALL mkdir build
CALL cd build
CALL cmake .. -G "MinGW Makefiles" -B build -DCMAKE_BUILD_TYPE=Release
popd
PAUSE

