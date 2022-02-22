# CAVES
# Minecraft 1.12.2 c/c++ cave generator with tnt blocks

Including CodeBlocks and mingw64 seh compiler (Windows)

Mingw64 seh compiler:

https://sourceforge.net/projects/mingw-w64/files/Toolchains%20targetting%20Win64/Personal%20Builds/mingw-builds/8.1.0/threads-posix/seh/x86_64-8.1.0-release-posix-seh-rt_v6-rev0.7z/download

Codeblocks noinstall:

https://sourceforge.net/projects/codeblocks/

unzip both files in directory codeblocks

Check directory screenshots for CodeBlocks settings (also in caves.cbd file, except Toolchain execuatables in Compiler settings)

Point Settings->Compiler->Toolchain executables to <DRIVELETTER>\:<PATH_TO>\CAVES\codeblocks\mingw64\bin

./bin/caves.exe (executable, call from directory CAVES) (set path)

./set_path.bat (clickable, set path to ./bin && ./codeblocks && ./codeblocks/mingw64/bin && open command shell)

./bin/cb.bat (start CodeBlocks from directory CAVES, do not click, start from command line after clicking set_path.bat)

./bin/compile.bat (compile with CodeBlocks from command line after clicking set_path.bat)

./src/make.bat (compile with ./CodeBlocks/mingw54/bin/g++.exe from command line from within directory ./src)

./Minecraft (1.12.2 && 1.18.1 level.dat, .mcfunctions + samples, for 1.12.2 in saves/caves/data, for 1.18.1 in saves/caves/datapacks, mods, version installers, resourcepacks && shaderpacks)

./tunnels.txt (Future use for setting constants variables formula's used for shaping)

# Forge Server 1.18.1 on 83.83.222.154

(https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/1.18.1/installers/forge-1.18.1-39.0.79-installer.jar)

***
Tip: If you want to play on a (local) server, with more players, while only having one account, you can do the following:

1) Disconnect the computer from the internet, by pulling the cable or shutting it off in the os.

2) Edit the launcher_accounts.json file (in windows in %appdata%\.minecraft) or in Ubuntu in your .minecraft dir in home. Change the name, don't use spaces but underscore if needed.

3) Then start the Minecraft launcher, it will say you only can play offline. Start. You now are under a different name, so you can log into the server with multiple players, all with different names, otherwise the server disconnects same names...

4) Of course reconnect to the net.

Also don't forget to set the online-mode=false in the server.properties besides the usual stuff like ip address etc.

Also when playing with people outside your home network you need to port forward your router, with the ip the server is on and the port its using. Tip: If it won't work probably ranges from other port forwards overlap yours.
Then you also need to provide your external ip instead of the internal to other players.
***
# Have fun!
***
If you get errors, or this manual is not working like it pretends, plz report then we can adjust it with more information. Also when having suggestions or made some changes or code yourself with this repo, please make issue a notice and share. This is just one example on how to create whole Minecraft worlds (you can stack them with Cubic Chunks eventually) in a simple way. In the MCEditor directory you can find a file called test.cpp, music.cpp, and paint.cpp giving more examples on how to build region files from scratch, like include music systems, and multiple command command blocks, like used in my other Minecraft world repo's. Like how to build Gray coded ordered commandblocks with multiple commands in domino effect style. In combination with .mcfunctions you could make code where like whole castles just pop out of the command blocks or .mcfunctions.
***
# Suggestions needed!!!

Goal is to set up a platform where worlds can by easily created from 2d drawings, 3d objects, code, commandblocks, .mcfunctions etc. With an easy to use interface. Any help is appreciated. Nice would be a saving to .nbt in the new 1.13+ structure (now 1.12.2)
***
          
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.05.15.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.25.01.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.26.13.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.26.28.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.26.48.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.27.06.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.27.28.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.28.12.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.29.26.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.29.41.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.30.41.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.30.51.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.31.25.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.31.42.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.33.12.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.33.27.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.33.59.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.34.33.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.35.10.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.35.47.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.36.44.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.36.54.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.37.05.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.37.26.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.38.08.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.39.12.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.39.40.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.40.08.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.40.40.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.42.01.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.42.27.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.44.49.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.45.11.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.49.33.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.52.01.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.53.13.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.53.40.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.54.20.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.54.41.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.55.18.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.56.07.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.56.23.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.58.07.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.58.32.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.58.56.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.59.23.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.59.39.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.03.32.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.03.59.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.05.32.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.06.40.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.07.06.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.08.02.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.08.24.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.08.48.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.09.03.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.12.02.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.13.23.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.13.50.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.14.07.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.14.26.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.14.40.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.15.20.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.15.39.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.16.06.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.16.35.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.16.52.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.17.26.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.20.14.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.20.34.jpg)
![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_07.21.18.jpg)
