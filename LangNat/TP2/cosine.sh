#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage : cosine.sh file1 file2"
    exit 1
fi

LC_ALL=C join $1 $2 | awk '{print }'
