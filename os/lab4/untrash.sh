#!/bin/bash

readonly TRASH_HOME="$HOME"
readonly TRASH_DIR="$TRASH_HOME/.trash"
readonly TRASH_LOG="$TRASH_HOME/.trash.log"

readonly SEP="///"

err() {
  echo "$*" >&2
  exit 1
}

usage() {
  err "Usage: $0 <file>"
}

(( $# != 1 )) && usage

file="$1"
entries=$(grep -s "${file}${SEP}" "$TRASH_LOG" || err "No such file")
for entry in $entries; do
  read -r path link <<<"$(echo "$entry" \
    | awk -F "$SEP" '{ print $1" "$2 }')"
  echo "$path"
  echo "Is this the file that you want? (Y/N)"
  
  read -r response
  case "${response^^}" in
    Y|"")
      dir="$(dirname "$path")"
      [[ ! -d "$dir" ]] \
        && echo "This directory doesn't exist anymore" \
        && echo "Your file will be restored into $HOME" \
        && dir="$HOME"
      cd "$dir" \
        && ln "$TRASH_DIR/$link" "$file" \
        && rm "$TRASH_DIR/$link" \
        && sed -i "\|$entry|d" "$TRASH_LOG" \
        && echo "File has been successfully restored" \
        && break
      ;;
    N)
      :
      ;;
    *)
      err "Incorrect option"
      ;;
  esac
done
