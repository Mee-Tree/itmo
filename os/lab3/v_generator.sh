#!/bin/bash
rm .return 2> /dev/null
while true; do
  read line
  echo "$line" > pipe
  code=$(cat .return 2> /dev/null) && exit $code
done
