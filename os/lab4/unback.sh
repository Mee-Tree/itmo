#!/bin/bash

readonly DATE_REGEX="[0-9]{4}-[0-9]{2}-[0-9]{2}"
readonly BACKUP_HOME="$HOME"
readonly RESTORE="$HOME/restore"
[[ -d "$RESTORE" ]] || mkdir "$RESTORE"

latest_backup=$(find "$BACKUP_HOME" -maxdepth 1 -name "Backup-*" \
  | sort -t '-' -k 2  \
  | tail -1)

[[ -z "$latest_backup" ]] \
  && echo "Nothing to restore" \
  && exit 1

for file in "$latest_backup/"*; do
  [[ ! "$file" =~ \.$DATE_REGEX$ ]] \
    && cp -r "$file" "$RESTORE"
done

