#!/bin/bash
# Generates a random sentence given a language model (LM) file in the format:
# w1 w2 w3 ... wn score
# words in n-grams must be separated by spaces, 
# score must be separated from preceding n-gram by tab
# score must be numerical, integer or real

lmfile=$1
randomness=3                         # higher value => weider sentences

pref="<s>"                           # prefix to start a sentence
sent=""                              # resulting sentence initialized empty
while [ "$cw" != "</s>" ]; do        # while sentence end not reached
  cw=`echo $pref | awk '{print $1}'` # chosen word = first of prefix
  sent=`echo $sent $cw`              # append chosen word to resulting sentence  
  pref=`cat $lmfile |                
  grep "^$pref " |                   # search prefix in LM file
  sort -nr -t "	" -k 2,2 |           # sort from most probable to less probable
  head -n $randomness |              # keep only top-$randomness most probable
  shuf -n 1 |                        # shuffle them and choose one arbitrarily
  awk 'BEGIN{FS="\t"}{print $1}'  |  # keep only the n-gram, remove the score
  cut -d " " -f 2- |                 # next prefix starts from 2nd word of ngram
  sed -E 's/(\.|]|\[)/\\\\&/g'`      # escape dot and brackets for grep
  #echo "pref=$pref, chosen-word=$cw" # uncomment for debugging 
done
echo $sent | sed -E -e 's@ ?</?s> ?@@g' -e 's/\\//g'
