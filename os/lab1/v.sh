#!/bin/bash
date="[[:alpha:]]{3} [0-9]{1,2} [0-9]{1,2}:[0-9]{1,2}:[0-9]{1,2}"
journalctl | grep -E "^${date}[^:]+:[^:]+INFO" > "info.log"
