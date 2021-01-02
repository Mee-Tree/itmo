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

log() {
  echo "${1}${SEP}${2}" >> "$TRASH_LOG"
}

(( $# != 1 )) && usage

[[ ! -d "$TRASH_DIR" ]] && mkdir "$TRASH_DIR"

abs_filename="$(readlink -f "$1")"
[[ ! -f "$abs_filename" ]] && err "No such file"

link_name="$(date +'%Y-%m-%dT%H-%M-%S')"

cd "$TRASH_DIR" \
  && ln "$abs_filename" "$link_name" \
  && rm "$abs_filename" \
  && log "$abs_filename" "$link_name"

