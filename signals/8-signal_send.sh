#!/usr/bin/env sh

# Simple script to send a QUIT signal to a process

# This script takes a single argument, which is the process ID (pid) of the process
# you want to send the QUIT signal to;
# It checks if the correct number of arguments is passed, displays the usage message if not,
# and proceeds to send the signal if correct

if [ "$#" -ne 1 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

kill -s QUIT "$1"
