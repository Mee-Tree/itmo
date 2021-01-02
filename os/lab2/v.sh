#!/bin/bash
prev_ppid=0
sleep_sum=0
children_cnt=0

while IFS= read -r line; do
  split=($(awk -F "\t:\t" '{ for (i=1; i<=3; ++i) 
    { split($i, s, "="); printf s[2]" " } }' <<< "$line"))
  if [[ ${split[1]} -ne $prev_ppid ]]; then
    avg_sleep=$(bc -l <<< "$sleep_sum / $children_cnt")
    echo "Average_Sleeping_Children_of_ParentID=$prev_ppid is $avg_sleep"
    prev_ppid=${split[1]}
    sleep_sum=${split[2]}
    children_cnt=1
  else
    sleep_sum=$(bc -l <<< "$sleep_sum + ${split[2]}")
    ((++children_cnt))
  fi
  echo -e "$line"
done <<< $(./iv.sh)

avg_sleep=$(bc -l <<< "$sleep_sum / $children_cnt")
echo "Average_Sleeping_Children_of_ParentID=$prev_ppid is $avg_sleep"
