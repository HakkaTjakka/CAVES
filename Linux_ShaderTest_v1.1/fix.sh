#!/bin/bash

#ls -t region/*.mca > filenames.txt

ls -tr saves/caves/region/*.mca > filenames.txt

for line in $(cat filenames.txt)
do
	echo "Filename: $line"
	./make_caves repack $line fix
done

# read -r FILENAME < filename.txt
# echo "Filename: $FILENAME"
