#!/bin/bash
(crontab -l 2> /dev/null ; echo "*/5 * * * 1 ~/lab3/i.sh") | crontab -
