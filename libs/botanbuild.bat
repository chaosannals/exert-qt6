@echo off

set QT_BIN_DIR=D:\Qt\6.2.1\mingw81_64\bin
set QT_MINGW64_DIR=D:\Qt\Tools\mingw810_64\bin
set PATH=%QT_MINGW64_DIR%;%QT_BIN_DIR%;%PATH%

cd botan

@echo on
mingw32-make

cd ..
