@echo off

mklink /D "%CD%\saves" <full_path_to_saves_dir>
mklink /D "%CD%\shaderpacks" <full_path_to_shaderpacks_dir>

pause

rem You can use this in your %appdata%\Roaming\.minecraft directory, if you like
rem (like C:\Users\<your username>\AppData\Roaming\.minecraft)

rem First rename the original like: ren saves saves.bak

rem Source and destination directory name must be the full directory path when this cmd batch is run as administrator ,
rem Because then this .bat file starts in your C:\WINDOWS\system32 directory.