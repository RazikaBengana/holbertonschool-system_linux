#!/usr/bin/env sh

# This script sets up trap handlers for specific signals;
# When an ABRT, IO, or TERM signal is received, it executes the specified command

# Trap and handle ABRT, IO, and TERM signals by printing "Nope" to the console
trap "echo Nope" ABRT IO TERM
