@echo off
pushd %~dp0\..\
CALL Thirdparty\premake\premake5.exe vs2022
popd
PAUSE
