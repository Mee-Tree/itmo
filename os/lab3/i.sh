#!/bin/bash 
start_time="$(date +"%F_%T")"
cd ~ && mkdir test && {
  echo "catalog test was created successfully" >> report ; touch test/"$start_time" 
}

url="www.net_nikogo.ru"
ping -c 1 $url &> /dev/null || echo "[$(date +"%F %T")] $url: Name or service not known" >> report
