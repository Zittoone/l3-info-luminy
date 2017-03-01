#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Usage : categorize.sh file"
    exit 1
fi

cuisine=0
ia=0
football=0
k=10

echo "" > result.txt 

for i in $(ls train-vec)
do
  ./cosine.sh train-vec/$i $1 >> result.txt
done

sort -nr result.txt | head -n 10 | sed -E "s/.*(cuisine|football|ia).*/\1/g" | sort | uniq -c | head -n 1
