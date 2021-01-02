#!/bin/bash

SEQUENCE=($(seq 1 1 10))
arr=()

while (( ${#arr[@]} < $1 )); do
  arr+=(${SEQUENCE[@]})
done