# update

In this version you can use the command line option 'repack', like ./make_caves repack region/r.3.4.mca to read and then write a region file where the blocklight & skylight is recalculated (bug in 1.12.2 version). In my current MC 1.12.2 version with Forge 1.12.2 there is no option 'Optimize World' in the world selection menu under the 'Edit' button. (Also see: https://github.com/HakkaTjakka/CAVES/blob/main/Linux_ShaderTest_v1.1/saves/caves/repack.sh)

https://github.com/HakkaTjakka/CAVES/blob/6b1443e1713f1f65b47534c35d963cc0b60e4db6/Linux_ShaderTest_v1.1/src/make_caves.cpp#L1054

If you need the same function in the Windows version you need to adapt the source yourself, using this as an example. I'm on Ubuntu Linux (4ever).
Of course i can do it for you on request.
***
For running a Minecraft server on Forge (1.18.1) you need to install Java version 17:

sudo apt-get install oracle-java17-installer oracle-java17-set-default

and

sudo add-apt-repository ppa:linuxuprising/java -y
***
For compiling with Linux (Ubuntu 20.04 in my case) install the following:

For using zlib under Ubuntu install with:

sudo apt-get install zlib1g-dev

or

sudo apt install zlib1g

curses.h:

sudo apt-get install libncurses5-dev libncursesw5-dev
***
For installing the SFML libraries:

sudo apt-get install libsfml-dev
***
Upgrading to include SFML windows for future output while generating caves (like top-view/side-view/front-view of region file(s))

cd src

to compile from bash: ./make_caves.sh

to compile with make (uses Makefile): make

Created make_caves.cbp in src for use with CodeBlocks
***
With the make.sh you can compile the caves program:

Previous now in directory: src_prev

cd src_prev

./make.sh

It then produces the caves executable one directory level up, where there is also the template/region/r.0.0.mca file
***
make.sh:

g++ -O3 -w -std=c++17 -m64 -c cave.cpp -lsfml-system

g++ -O3 -w -std=c++17 -m64 -c functions.cpp

g++ -O3 -w -std=c++17 -m64 -c MCEditor/globals.cpp

g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCACoder.cpp

g++ -O3 -w -std=c++17 -m64 -c MCEditor/MCEditor.cpp

g++ -O3 -w -std=c++17 -m64 -c MCEditor/NBTCoder.cpp

g++ -o ../caves cave.o functions.o globals.o MCACoder.o MCEditor.o NBTCoder.o -s -m64 -lm -lsfml-system -lz
***
Created caves.cbp in src_prev for use with CodeBlocks
***
When installing a server under Linux with the forge-1.18.1-39.0.79-installer.jar file from CAVES/Minecraft/1.18.1/installers i included my server.properties file and user_jvm_args.txt and run.sh

Also edit fml.toml in the config dir and set maxThreads = 4 (mine is 4) to maximum number of processor cores on your cpu.

Also use:

sudo cpupower frequency-set -g performance

for maximum cpu usage...
***
Tip: If you want to play on a (local) server, with more players, while only having one account, you can do the following:

1) Disconnect the computer from the internet, by pulling the cable or shutting it off in the os.

2) Edit the launcher_accounts.json file (in windows in %appdata%/.minecraft) or in Ubuntu in your .minecraft dir in home. Change the name, don't use spaces but underscore if needed.

3) Then start the Minecraft launcher, it will say you only can play offline. Start. You now are under a different name, so you can log into the server with multiple players, all with different names, otherwise the server disconnects same names...

4) Of course reconnect to the net.

Also don't forget to set the online-mode=false in the server.properties besides the usual stuff like ip address etc.

Also when playing with people outside your home network you need to port forward your router, with the ip the server is on and the port its using. Tip: If it won't work probably ranges from other port forwards overlap yours.
Then you also need to provide your external ip instead of the internal to other players.
***
Have fun!
***
If you get errors, or this manual is not working like it pretends, plz report then we can adjust it with more information. Also when having suggestions or made some changes or code yourself with this repo, please make issue a notice and share. This is just one example on how to create whole Minecraft worlds (you can stack them with Cubic Chunks eventually) in a simple way. In the MCEditor directory you can find a file called test.cpp, music.cpp, and paint.cpp giving more examples on how to build region files from scratch, like include music systems, and multiple command command blocks, like used in my other Minecraft world repo's. Like how to build Gray coded ordered commandblocks with multiple commands in domino effect style. In combination with .mcfunctions you could make code where like whole castles just pop out of the command blocks or .mcfunctions.
***
Goal is to set up a platform where worlds can by easily created from 2d drawings, 3d objects, code, commandblocks, .mcfunctions etc. With an easy to use interface. Any help is appreciated. Nice would be a saving to .nbt in the new 1.13+ structure (now 1.12.2)
 

