#!/bin/bash

k=$1
while (( k-- > 0 )); do
  ./newmem.bash "$2" &
  sleep 1
done