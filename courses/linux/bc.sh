#!/bin/bash
#
result=1
for ((i = 1; i <= 1000; i += 2)); do
	result=$(echo "$result * $i" | bc)
done
echo "$result"
