#!/bin/bash
for pid in $(ps -eo pid); do
  if [[ ! -f "/proc/$pid/io" ]]; then continue; fi
    echo -n $pid
  awk -F ": " '$1 == "read_bytes" { print " "$2 }' "/proc/$pid/io"
done > "tmp.txt"

sleep 1m

while IFS= read -r line; do
  split=($line)
  pid="${split[0]}"
  if [[ ! -f "/proc/$pid/io" ]]; then continue; fi
    echo -n $pid
  awk -F ": " -v bytes="${split[1]}" 'ORS=""; $1 == "read_bytes" { 
    diff = $2 - bytes; print ":"diff":" 
  }' "/proc/$pid/io"
  cat "/proc/$pid/cmdline" && echo
done < "tmp.txt" | sort -t : -nk 2 | tail -3 && rm "tmp.txt"
