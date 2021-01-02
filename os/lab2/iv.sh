#!/bin/bash
format="ProcessID=%d\t:\tParent_ProcessID=%d\t:\tAverage_Running_Time=%f\n"

for pid in $(ps -eo pid | tail -n +2); do
    if [[ ! -d "/proc/$pid/" ]]; then continue; fi
    cd "/proc/$pid/"
    ppid=$(awk '$1 == "PPid:" { print $2 }' "status")
    expr=$(awk '$1 == "se.sum_exec_runtime" { printf $3 };
                $1 == "nr_switches" { printf "/%f",$3 }' "sched")
    art=$(bc -l <<< "$expr")
    echo "$pid $ppid $art"
done | sort -nk 2 | awk -v format="$format" '{ printf format, $1, $2, $3 }'
