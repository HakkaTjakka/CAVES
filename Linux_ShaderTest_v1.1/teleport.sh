#!/bin/bash

ls -t saves/caves/region/*.mca > filenames.txt

for line in $(cat filenames.txt)
do
	echo "Filename: $line"
	./make_caves repack $line teleport
done

# read -r FILENAME < filename.txt
# echo "Filename: $FILENAME"
