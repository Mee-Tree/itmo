#!/bin/bash
LINE=""
ANSWER=""

while [[ "$LINE" != "q" ]]; do
  if [[ -z "$ANSWER" ]]; then
    ANSWER="$LINE"
  else 
    ANSWER="$ANSWER $LINE"
  fi
  read LINE
done

echo "$ANSWER"
