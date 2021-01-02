#!/bin/bash
for pid in $(ps -eo pid); do
  if [[ ! -f "/proc/$pid/status" ]]; then continue; fi
  awk -F ":" '$1 == "VmSize" { print $2 }' "/proc/$pid/status"
done | sort -n | tail -1
