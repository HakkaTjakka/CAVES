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

            