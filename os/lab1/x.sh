#!/bin/bash
man bash | grep -Eo "[[:alpha:]]{4,}" | sort | uniq -c | sort -nr | head  -3
