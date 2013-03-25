#!/bin/bash

#Data collection
#Getting list from file
#Creating file for each calls
#Collecting a single file
touch output
touch output1
touch ind
echo "" > output
echo "" > output1

lttng create 1
lttng enable-event -a -k
lttng start

i=1

while [ true ]
do
    #wait for a sec
    #here use the output of previous logs
    sleep 1
    echo "" > ind
    cat list | while read LINE
    do
        cat output | grep "$LINE" > test1
        cat test1 | wc -l >> ind
    done
    i=$((1-i))
    #create the next session and destroy this session
    lttng create $i
    lttng enable-event -a -k
    lttng start
    lttng stop $((1-i))
    lttng view > output1
    lttng destroy $((1-i))
    #calculate the diff and find common k lines
    max_len=`cat output1 | wc -l`
    diff_line=`diff --suppress-common-lines output output1 | grep "<.*$"`
    tail -n +$((max_len + 1 - diff_len)) output1 > output
done
