# g++ -O3 -w -std=c++17 -m64 -c main.cpp
# g++ -O3 -w -std=c++17 -m64 -c make_caves.cpp
# g++ -O3 -w -std=c++17 -m64 -c functions.cpp
# g++ -O3 -w -std=c++17 -m64 -c MCEditor/globals.cpp
# g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCACoder.cpp
# g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCEditor.cpp
# g++ -O3 -w -std=c++17 -m64 -c MCEditor/NBTCoder.cpp
# g++ -o ../make_caves main.o make_caves.o functions.o globals.o MCACoder.o MCEditor.o NBTCoder.o -s -m64 -lm -lsfml-system -lsfml-window -lsfml-graphics -lz

CC = g++
CFLAGS  = -O3 -w -std=c++17 -m64
LDLAGS  = -s -m64 -lm -lsfml-system -lsfml-window -lsfml-graphics -lz
OBJS = obj/main.o obj/make_caves.o obj/functions.o obj/MCEditor/globals.o obj/MCEditor/MCACoder.o obj/MCEditor/MCEditor.o obj/MCEditor/NBTCoder.o

default: ../make_caves

../make_caves: $(OBJS)
	$(CC) -o ../make_caves $(OBJS) $(LDLAGS)

obj/main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp -o obj/main.o

obj/make_caves.o: make_caves.cpp
	$(CC) $(CFLAGS) -c make_caves.cpp -o obj/make_caves.o

obj/functions.o: functions.cpp
	$(CC) $(CFLAGS) -c functions.cpp -o obj/functions.o

obj/MCEditor/globals.o: MCEditor/globals.cpp MCEditor/globals.h
	$(CC) $(CFLAGS) -c MCEditor/globals.cpp -o obj/MCEditor/globals.o

obj/MCEditor/MCACoder.o: MCEditor/MCACoder.cpp MCEditor/MCACoder.h MCEditor/globals.h 
	$(CC) $(CFLAGS) -c MCEditor/MCACoder.cpp -o obj/MCEditor/MCACoder.o

obj/MCEditor/MCEditor.o: MCEditor/MCEditor.cpp MCEditor/MCEditor.h MCEditor/globals.h 
	$(CC) $(CFLAGS) -c MCEditor/MCEditor.cpp -o obj/MCEditor/MCEditor.o

obj/MCEditor/NBTCoder.o: MCEditor/NBTCoder.cpp MCEditor/NBTCoder.h
	$(CC) $(CFLAGS) -c MCEditor/NBTCoder.cpp -o obj/MCEditor/NBTCoder.o

clean: 
#	$(RM) count *.o *~
	$(RM) obj/*.o
	$(RM) obj/MCEditor/*.o

$(OBJS): | obj
$(OBJS): | obj/MCEditor

obj:
	mkdir -p obj

obj/MCEditor:
	mkdir -p obj/MCEditor

