@echo off
pushd %~dp0\..\
CALL mkdir build
CALL cd build
CALL cmake .. -G "Visual Studio 17 2022" -B build -DCMAKE_BUILD_TYPE=Release
popd
PAUSE

