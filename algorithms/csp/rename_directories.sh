#!/bin/bash

for i in $(find . -maxdepth 1 -type d); do
	echo "old name: $i"
	NEWNAME=$(echo "$i" | sed -E 's/(\.\/20)(.*)/\2/')
	echo "new name: $NEWNAME"
	mv "$i" "$NEWNAME"
done
