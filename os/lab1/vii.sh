#!/bin/bash
email="[[:alnum:]_%.+-]+@[[:alnum:]_.-]+\.[[:alpha:].]{2,6}"
grep -IEorh "$email" "/etc" | uniq | awk 'ORS=", " { print }' > emails.lst
