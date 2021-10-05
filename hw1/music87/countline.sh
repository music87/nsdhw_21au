#!/bin/bash
# it's a shell script version of countline.py

if [ "$#" -lt "1" ]; then
  echo missing file name

elif [ "$#" -gt "1" ]; then
  echo only one argument is allowed

else
  fname=$1
  if [ -r $fname ]; then 
  # -r file return True if file exists and is readable.
  N=$(cat $fname | wc -l)
  echo $N lines in $fname
  else
    echo $fname not found
  fi
fi
