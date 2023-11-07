#!/bin/bash

echo "Script name: $0"
echo "Number of arguments: $#"
echo "All arguments (as a single string): $*"

# Using a for loop to process each argument
echo "Processing arguments using a for loop:"
for arg in "$@"; do
    echo "Argument: $arg"
done

# Using a while loop to process arguments until none are left
echo "Processing arguments using a while loop:"
count=1
while [ $# -gt 0 ]; do
    echo "Argument $count: $1"
    shift
    count=$((count + 1))
done
