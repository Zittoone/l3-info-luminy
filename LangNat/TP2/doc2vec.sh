#!/bin/bash

if [ $# -ne 1 ]
then
  echo "Usage : doc2vec.sh FILE_PATH"
  exit 1
fi

if ! [ -f "$1" ]
then
  echo "Not a valid file"
  exit 1
fi

sed 's/ /\n/g' $1 | sort | uniq -c | sort -r | awk '{print $2 "\t" $1}' | LC_ALL=C sort

exit 0
