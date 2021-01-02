#!/bin/bash
echo $$ > .pid
mode="+" ; val=1

usr1() { mode="+"; }
usr2() { mode="*"; }
term() { mode="TERM"; }

trap 'usr1' USR1
trap 'usr2' USR2
trap 'term' SIGTERM

while true; do
  case $mode in
    '*'|'+') val=$((val $mode 2)) ; echo $val ;;  
    TERM) echo "Terminated by SIGTERM" ; exit ;;
  esac
  sleep 1
done
