@echo off
pushd %~dp0\..\
CALL Thirdparty\premake\premake5.exe gmake2
popd
PAUSE