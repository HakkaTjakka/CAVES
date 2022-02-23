g++ -O3 -w -std=c++17 -m64 -c cave.cpp -lsfml-system
g++ -O3 -w -std=c++17 -m64 -c functions.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/globals.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCACoder.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCEditor.cpp
g++ -O3 -w -std=c++17 -m64 -c MCEditor/NBTCoder.cpp
g++ -o ../caves cave.o functions.o globals.o MCACoder.o MCEditor.o NBTCoder.o -s -m64 -lm -lsfml-system -lz
