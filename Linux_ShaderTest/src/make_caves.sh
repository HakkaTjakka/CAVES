g++ -O3 -w -std=c++17 -m64 -c main.cpp
g++ -O3 -w -std=c++17 -m64 -c shaders.cpp
g++ -O3 -w -std=c++17 -m64 -c make_caves.cpp
g++ -O3 -w -std=c++17 -m64 -c functions.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/globals.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCACoder.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCEditor.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/NBTCoder.cpp
g++ -o ../make_caves shaders.o main.o make_caves.o functions.o globals.o MCACoder.o MCEditor.o NBTCoder.o -s -m64 -lm -lsfml-system -lsfml-window -lsfml-graphics -lz -lX11 -lglut -lGLU -lGL

