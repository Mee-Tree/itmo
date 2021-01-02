#!/bin/bash

REPORT="log/report.log"
SEQUENCE=($(seq 1 1 10))

echo "" > "$REPORT"
./helper.bash &

cnt=0
arr=()

while true; do
  ((++cnt))
  arr+=(${SEQUENCE[@]})
  if (( cnt == 100000 )); then
    echo "${#arr[@]}" >> "$REPORT"
    cnt=0
  fi
done