#!/bin/bash
shopt -s nullglob

readonly BACKUP_HOME="$HOME"
readonly BACKUP_REPORT="$BACKUP_HOME/backup-report"
readonly SOURCE="$HOME/source"

readonly WEEK_AGO=$(date -d 'now -7 days' +%F)
readonly DATE=$(date +%F)

report() {
  echo -e "[$(date +'%Y-%m-%dT%H:%M:%S')] $*" >> "$BACKUP_REPORT"
}

copy() {
  cp -r "$1" "$2" \
    && report " - $(basename "$1") has been copied into $2"
}

backup_dir=""

for dir in "$BACKUP_HOME"/Backup-*; do
  backup_date=$(echo "$dir" | awk -F "Backup-" '{ print $2 }')
  if [[ $backup_date > $WEEK_AGO ]]; then
    backup_dir="$dir"
  fi
done

if [[ -z "$backup_dir" ]]; then
  backup_dir="$BACKUP_HOME/Backup-$DATE"
  mkdir "$backup_dir" \
    && report "Directory $backup_dir has been successfully created"
  for file in "$SOURCE"/*; do
    copy "$file" "$backup_dir"
  done
else
  for file in "$SOURCE"/*; do
    backup_file="$backup_dir/$(basename "$file")"
    if [[ -e "$backup_file" ]]; then
      size=$(stat -c %s "$file")
      backup_size=$(stat -c %s "$backup_file")
      
    if ((size != backup_size )); then
      mv "$backup_file" "${backup_file}.$DATE" \
        && report " - Previous file $backup_file was renamed to $(basename "$file").$DATE"
    else
      continue
    fi
  fi
  copy "$file" "$backup_dir"
  done
fi
