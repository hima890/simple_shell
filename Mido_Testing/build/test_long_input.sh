#!/bin/bash

# Generate a very long empty input string
very_long_empty_input=$(printf "\n%.0s" {1..10000})

# Echo the very long empty input to the shell
echo -n "$very_long_empty_input" | ./hsh
