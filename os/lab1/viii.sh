#!/bin/bash 
sort -g -t ":" -k 3 "/etc/passwd" | awk -F ":" '{ printf "%d %s\n",$3,$1 }'
