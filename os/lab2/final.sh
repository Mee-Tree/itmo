#!/bin/bash
for pid in $(ps -eo pid); do
  [[ ! -f "/proc/$pid/statm" ]] && continue
  diff=$(awk '{ print $2 - $3 }' "/proc/$pid/statm")
  echo $((diff * $(getconf PAGESIZE))) "B"
done | sort -n | tail -1
