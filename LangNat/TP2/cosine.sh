#!/bin/bash

if [ $# -ne 2 ]
then
    echo "Usage : cosine.sh file1 file2"
    exit 1
fi
dpab=0
dpaa=0
dpbb=0

LC_ALL=C join $1 $2 > temp.txt

#denominateur
dpab=$(LC_ALL=C join $1 $2 | awk 'BEGIN{scalaire=0}{scalaire = scalaire + ($2 * $3)} END{print scalaire}')
#norme document A
dpaa=$(LC_ALL=C join $1 $2 | awk 'BEGIN{norme=0}{norme = norme + $2^2}END{print sqrt(norme)}')
#norme document B
dpbb=$(LC_ALL=C join $1 $2 | awk 'BEGIN{norme=0}{norme = norme + $3^2}END{print sqrt(norme)}')

res=$(bc -l <<< "$dpab / ( $dpaa * $dpbb )")

echo "$res $1 $2"
