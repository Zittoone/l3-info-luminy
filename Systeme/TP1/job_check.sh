#!/bin/bash

function prendre_peripherique()
{
   local nom="$1"
   while ! mkdir "$nom" 2>/dev/null; do
      sleep 0.01s
   done
}

prendre_peripherique $1

for ((I=0; I<90000*6; I++))
do J=I
done



exit 0