@echo off
set PATH=%CD%\bin;%CD%\codeblocks;%CD%\codeblocks\mingw64\bin;%PATH%
cd src
rem @call cmd /k codeblocks caves.cbp
start codeblocks caves.cbp
rem --no-dde rem --no-splash-screen
cd ..
