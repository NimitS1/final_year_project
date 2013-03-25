#!/bin/bash

#echo "testing file leng"
#i=`cat size.sh | wc -l`
max_len=`cat a | wc -l`
diff_len=`diff --suppress-common-lines a b | grep "<.*$" | wc -l`
tail -n +$((max_len + 1 - diff_len)) b
echo $i
