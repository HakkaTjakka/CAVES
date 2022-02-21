@echo off
set PATH=..\codeblocks\mingw64\bin;%PATH%
if not exist obj mkdir obj
if not exist obj\MCEditor mkdir obj\MCEditor
if not exist ..\bin\ mkdir ..\bin\
echo on

g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c cave.cpp -o obj\cave.o
g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c functions.cpp -o obj\functions.o
g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c MCEditor\globals.cpp -o obj\MCEditor\globals.o
g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c MCEditor\MCACoder.cpp -o obj\MCEditor\MCACoder.o
g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c MCEditor\MCEditor.cpp -o obj\MCEditor\MCEditor.o
g++.exe -O3 -w -std=c++17 -m64 -DSFML_STATIC -Iinclude -c MCEditor\NBTCoder.cpp -o obj\MCEditor\NBTCoder.o
g++.exe -Llib -o ..\bin\caves.exe obj\cave.o obj\functions.o obj\MCEditor\globals.o obj\MCEditor\MCACoder.o obj\MCEditor\MCEditor.o obj\MCEditor\NBTCoder.o  -s -m64 -static-libgcc -static-libstdc++ -fstack-protector -Wl,-u,vfscanf  -lm  lib\libsfml-graphics-s.a lib\libsfml-window-s.a lib\libsfml-audio-s.a lib\libsfml-system-s.a lib\libsfml-network-s.a lib\libsfml-main.a lib\libz.a

pause 
