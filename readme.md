# CAVES
# Minecraft 1.12.2 c/c++ cave generator with tnt blocks

Added 2 more layers of bedrock against leaking exxabite floodfill because of height update (lots of empty space <0 in 1.18.1)

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

2) Edit the launcher_accounts.json file (in windows in %appdata%/.minecraft) or in Ubuntu in your .minecraft dir in home. Change the name, don't use spaces but underscore if needed.

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

Goal is to set up a platform where worlds can by easily created from 2d drawings, 3d objects (voxelizer is working, whole Holland was converted that way from Google 3d Earth into Minecraft BTE121 projection), code, commandblocks, .mcfunctions etc. With an easy to use interface. Any help is appreciated. Nice would be a saving to .nbt in the new 1.13+ structure (now 1.12.2)
***
On MCEditor: https://github.com/mingl0280/MCEditor

I've made some repo's where this code is used, and adapted it for some speed. I've made a (preliminary experimental prototyping program) named MinecraftWorldEditor. It is so called junk code, but the mechanisms work. For neat tiny version that used this (adapted) MCEditor code i'v made a new repo called 'caves', to show how it works in simple code.

My goal is to create some advanced Minecraft world generating platform including the following (90% of it already works in the MinecraftWorldEditor, but you need assistance to operate it).

A voxelizer that can convert Wavefront 3d objects into Minecraft 1.12.2 region files. This way whole of Holland is converted from Google Earth 3d (with a node.js downloading tool also on GitHub) into Build The Earth 121 projection. Converting it into 'stacked' region files that can be combined with Converter.jar (also on GitHub) into Cubic Chunks format (1.12.2).
3d objects can be loaded, real time animated, ffmpeg recorded, with interpolated camera positions, converted into large scale posters in different projections (like whole cities in orthographic projection like 30 x 15 meters), and converted into voxels. One or many 3d objects can that way be the source for Minecraft.

(closed) 3d objects can be made solid with the lighting algorithm, and/or using outside/outside of the triangles.

Also 2d drawings (program contains canvas with like 200 times 200 hd screens for scrolling and drawings) can be the source, like with use of a 3d maze generator.

With c/c++ code everything can be adapted / changed / calculated, and be converted into (for now) 1.12.2 region files. There can be multiple command commandblocks, containing hundreds of functions, and they also can be cascaded like domino's. So you can use 2d, 3d, and code to create almost anything.

Conversion of Minecraft data / voxels into Wavefront 3d files, that then can be loaded and animated again. It works through shaders. I'm working on a shader (geometry) where only the cube data is used as a voxel (one 3d point) and all necessary sides for rendering are being created in GPU.

Creating large posters on the large canvas out of whole Minecraft worlds with use of these shaders. (to do)

Creating an editor (2d/3d) for interactive building Minecraft worlds in 2d/3d, with use of 2d and 3d objects/data, and code, for high speed world generating. Eventually also using shaders to process data very fast. Shaders mostly are used to generate 2d drawings, but multiple 2d can be stacked to create 3d voxel data for worlds. Also 3d processing and generating can be done to produce voxel data in high speed.

There is an option for a build in Minecraft (1.12.2) server (Cuberite, also on GitHub) in the MinecraftWorldEditor that can be used for on the fly displaying generated region files in the game.

Voxel / region file data can be stored with the MCEditor for region files, in voxel files, or any other format. A secondary .nbt (Named Binary Tags) editor (also on GitHub by IDidMakeThat, adapted, speed up, and debugged, no memory leaks anymore...) that can be used for reading/writing encoding/decoding .nbt files. In where region files are stored, but they also can contain any other data. Like i'm using it to store the Wavefront 3d data into it, where only the data is present that is loaded into the gpu, after reading the Wavefront files, for compression and speed. That way i stored the whole of Holland from Google 3d. Also voxel data can be stored as pictures by slicing 3d voxel data up, and store them like a video with ffmpeg. Also for compression. Whole worlds can be stored that way as a video with compression (lossless), in several formats.

Use and generation of .mcfunction files to provide in game recursive command blocks for like fill things up (like water), or blow everything apart with tnt (with xplosives mod).

Like said the MinecraftWorldEditor is a preliminary experimental prototyping program, where all this code is inside (c/c++) one big executable, and is difficult to handle. There are some short manuals.

Aim of the game is to rewrite the whole system into a manageable system, where everything will be connected to a format everybody can use. Providing the use of all possibilities. The program can be the base of a new system, where all sorts of data can be used to generate and/or operate large scale worlds (Cubic Chunks Holland BTE121 projection is about 43.000 square km and 2 Terrabyte in size, and was downloaded from Google 3d, converted, and uploaded in two formats simultaneously in about 6 months).

Here are some examples of repo's made with the MCEditor code and MinecraftWorldEditor program:

Video's:

https://www.youtube.com/channel/UCdmRlIxcrXmkC7puY4s9Jzg

https://www.facebook.com/MinecraftWorldEditor/

Repo's:

https://github.com/HakkaTjakka/CAVES (Simplified MCEditor usage generating caves with tunnels filled with tnt)

https://github.com/HakkaTjakka/AQUAWORLD (World with aquariums that are (1.13+) filled with fish and coral with multiple command commandblocks under the level that are triggered as domino's in cascade)

https://github.com/HakkaTjakka/HOLLAND_BTE121_CUBIC_1 (Whole of The Netherlands in BTE121 projection in Cubic Chunks format, converted from Google 3d Earth into voxels into 1.12.2 region files in floors)

https://github.com/HakkaTjakka/MinecraftWorldEditor (Program that does the trick(s), lots of example code to be used)

https://github.com/HakkaTjakka/NL_TILE_MAP (Leaflet top view tile map of the BTE121 projection world of Holland)

https://github.com/HakkaTjakka/earth-reverse-engineering_github (Adapted code (node.js) for bulk downloading Google 3d data)

https://github.com/HakkaTjakka/PROJECT-CGI-BTE121-LEAFLET (Sample how to use c/c++ programs into cgi-bin in website together with SFML functions to convert images realtime on server site (can be anything...))

https://github.com/HakkaTjakka/SKULL-MAZE-REVISED (Demo of one Wavefront 3d object used for creating a whole world in Minecraft 1.12.2, with tents of thousands of kilometres rails)

https://github.com/HakkaTjakka/exxabites-floodfills (Samples of recursive command blocks (from exxabite who started that) for filling up stuff and/or place tnt in-game, 1.12.2 versions differ from 1.13+ versions)

https://github.com/HakkaTjakka/ABC3D-WORDVIEW-MINECRAFT-1.12.2 (3d scrabble in Minecraft using .mcfunction files only)

https://github.com/HakkaTjakka/BOOM (Part of Den Hague Holland converted from google 3d scale 3:1, with lots of tnt in surface/buildings and tunnels with tnt underneath)

https://github.com/HakkaTjakka/CREATE-MINECRAFT-1.12.2-AQUAWORLD-YOURSELF (Demo of MinecraftWorldEditor to build the aquaworld yourself from scratch using 2d images)

https://github.com/HakkaTjakka/AMSTERDAM_BTE (Amsterdam in BTE121 projection, used as 'mold' by people building Amsterdam in Minecraft)

https://github.com/HakkaTjakka/DENHAAG_BTE121 (Den Hague BTE121 projection)

https://github.com/HakkaTjakka/ENSCHEDE_BTE (Enschede BTE121 projection)

https://github.com/HakkaTjakka/RIO_BTE (Part of Rio BTE121 projection testing Cubic Chunks and how to make solid hills)

https://github.com/HakkaTjakka/Minecraft-1.12.2-Google-3d-New-York-2-1-TNT-Floodfill (Part of New York BTE121 projection)

https://github.com/HakkaTjakka/MCREPACKER (Repack region files for testing .nbt system from IDidMakeThat)

Anybody who wants to get involved in the project is welcome.

[![Demo CountPages alpha](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.25.01.jpg)](https://www.youtube.com/watch?v=5SJG3ie4RF8)
(Click to play vid)

![clipboard_small](https://github.com/HakkaTjakka/CAVES/blob/main/Minecraft/screenshots/2022-02-21_06.05.15.jpg)
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
