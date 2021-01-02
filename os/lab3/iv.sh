#!/bin/bash
cd ~/lab3
cpulimit -z -l 10 ./inf.sh &
./inf.sh &
./inf.sh &
