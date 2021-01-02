#!/bin/bash
file="full.log"
awk '{if ($3 == "(WW)") { $3 = "Warning:"; print } }' "/var/log/Xorg.0.log" > "$file"
awk '{if ($3 == "(II)") { $3 = "Information:"; print } }' "/var/log/Xorg.0.log" >> "$file"
cat "$file"
