#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage : gen-n-grams-count file n"
    exit 1
fi

lmfile=$1

a="<s>"
b="</s>"

cat $1 |
    sed -E "s|^(.*)$|${a} \1 ${b}|g" |          # tags <s> at the begining and </s> at the end 
    sed -E "s/ /\n/g" > $1-1word-line           # replace all space by line breaks


COUNTER=1
while [  $COUNTER -lt $2 ]; do
    let n=COUNTER+1
    tail -n +$n $1-1word-line > $1-1word-line-$COUNTER
    let COUNTER=n 
done

for f in $(ls | grep 1word-line) # files param of paste call concat. here
do
    files="$files $f"
done
paste -d' ' $files > $1.$2-grams

for f in $(ls | grep 1word-line) # delete files
do
    rm $f
done


cat $1.$2-grams | sort | uniq -c |
    awk '{for(i=2;i<=NF;i++){printf "%s ", $i}; printf "\t%d\n", $1}' > $1.$2-grams.count


