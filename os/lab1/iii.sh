#!/bin/bash
echo "~~~~~~~~~~~~"
echo "    MENU    "
echo "~~~~~~~~~~~~"

OPTIONS=("nano"
         "vi"
         "links"
         "exit")

PS3="Select one of the options above: "

select OPTION in "${OPTIONS[@]}"; do
  case $OPTION in
    nano) nano ;;
    vi) vi ;;
    links) links ;;
    exit) break ;;
    *) echo "Invalid option. Try again" ;;
  esac
done
