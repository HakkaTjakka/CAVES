For compiling with Linux (Ubuntu 20.04 in my case) install the following:

For running a Minecraft server on Forge (1.18.1) you need to install Java version 17:

sudo apt-get install oracle-java17-installer oracle-java17-set-default

and

sudo add-apt-repository ppa:linuxuprising/java -y
***
For using zlib under Ubuntu install with:

sudo apt-get install zlib1g-dev

or

sudo apt install zlib1g
***
For installing the SFML libraries:

sudo apt-get install libsfml-dev
***
With the make.sh you can compile the caves program:

cd src

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
When installing a server under Linux with the forge-1.18.1-39.0.79-installer.jar file from CAVES/Minecraft/1.18.1/installers i included my server.properties file and user_jvm_args.txt and run.sh
***
Tip: If you want to play on a (local) server, while only having one account, you can do the following:

1) Disconnect the computer from the internet, by pulling the cable or shutting it of in the os.

2) Edit the launcher_accounts.json file (in windows in %appdata%\.minecraft) or in Ubuntu in your .minecraft dir in home.

3) Then start the Minecraft launcher, it will say you only can play offline. Start. You now are under a different name, so you can log into the server with multiple players, all with different names, otherwise the server disconnects same names...

4) Of course reconnect to the net.

Also don't forget to set the online-mode=false in the server.properties besides the usual stuff like ip address etc.

Also when playing with people outside your home network you need to port forward your router, with the ip the server is on and the port its using. Tip: If it won't work probably ranges from other port forwards overlap yours.
Then you also need to provider your external ip instead of the internal.
***



