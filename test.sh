#!/bin/bash
# SCRIPT:  method1.sh
# PURPOSE: Process a file line by line with PIPED while-read loop.

FILENAME=$1
count=0
cat $FILENAME | while read LINE
do
       let count++
       echo "$count $LINE"
done

echo -e "\nTotal $count Lines read"
