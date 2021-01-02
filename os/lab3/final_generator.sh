#!/bin/bash
while true; do
  read -r line
  case $line in
    TERM) kill "$(cat .pid)" ; break ;;
    QUIT) kill -SIGQUIT "$(cat .pid)" ; break ;;
    KILL) kill -SIGKILL "$(cat .pid)" ; break ;;
    *) : ;;
  esac
done