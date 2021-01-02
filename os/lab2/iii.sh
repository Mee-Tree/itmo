#!/bin/bash
ps -ef --sort=start_time | awk -v pid=$$ '$2 != pid && $3 != pid { print $2 }' | tail -1
