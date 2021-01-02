#!/bin/bash
echo $$ > .pid
mode="RUNNING"

term() { mode="TERM"; }
quit() { mode="QUIT"; }

trap 'term' SIGTERM
trap 'quit' SIGQUIT

while true; do
  case $mode in
    RUNNING) : ;;  
    TERM) echo "Terminated" ; exit ;;
    QUIT) echo "Quit" ; exit ;;
  esac
done
