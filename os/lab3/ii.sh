#!/bin/bash
cd ~ && {
  at now + 2 minutes -f "lab3/i.sh"
  tail -n 0 -f report
}
