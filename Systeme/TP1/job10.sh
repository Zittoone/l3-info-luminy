#!/bin/bash

for ((I=0; I<10; I++)); do
   ./job.sh &
done

wait

exit 0
