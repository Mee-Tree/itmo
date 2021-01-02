#!/bin/bash
if [[ "$PWD" == "$HOME" ]]; then
  echo "exit 0"
  exit 0
else
  echo "exit 1"
  exit 1
fi
