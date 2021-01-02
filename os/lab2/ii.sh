#!/bin/bash
ps aux | awk '$11 ~ /^\/sbin\// { print $2 }' > "sbin.txt"
