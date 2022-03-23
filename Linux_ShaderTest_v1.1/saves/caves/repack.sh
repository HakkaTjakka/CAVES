#!/bin/bash

ls -t region/*.mca > filenames.txt

for line in $(cat filenames.txt)
do
	echo "Filename: $line"
	./make_caves repack $line $*
done

# read -r FILENAME < filename.txt
# echo "Filename: $FILENAME"
