#!/bin/bash

# This script reads input from stdin and converts it to uppercase

while read -r line; do
    echo "$line" | tr '[:lower:]' '[:upper:]'
done
