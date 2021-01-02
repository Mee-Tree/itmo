#!/bin/bash
shopt -s extglob
number=+([[:digit:]])
mode="+" ; val=1

(tail -f pipe) | 
while true; do
  read in
  case $in in
    '*'|'+') mode=$in ;;
    $number) val=$((val $mode $in)) ; echo $val ;;  
    QUIT) echo "Stopped" ; echo 0 > .return ; exit ;;
    *) echo "Illegal argument" ; echo 1 > .return ; exit 1 ;;
  esac
done
