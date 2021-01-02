#!/bin/bash
out="pscnt.txt"
ps ux -u "$USER" | awk 'NR > 1 {
  cmd = ""
  for (i = 11; i <= NF; ++i) { 
    cmd = cmd" "$i
  }
  printf "%s:%s\n",$2,cmd }' > tmp.txt
cat tmp.txt | wc -l > "$out" & cat tmp.txt >> "$out" & rm tmp.txt
