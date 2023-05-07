#! /bin/bash

prev_sent=$(netstat --statistics | grep -Eo '([0-9]+) segments received' | grep -Eo '[0-9]+')
prev_received=$(netstat --statistics | grep -Eo '([0-9]+) segments sent out' | grep -Eo '[0-9]+')
prev_total=$((prev_sent + prev_received))
prev_delta_total=0

while true; do
	sleep 60
	current_time=$(date +"%Y-%m-%d %H:%M")
	sent=$(netstat --statistics | grep -Eo '([0-9]+) segments received' | grep -Eo '[0-9]+')
	received=$(netstat --statistics | grep -Eo '([0-9]+) segments sent out' | grep -Eo '[0-9]+')
	total=$((sent + received))

	delta_sent=$((sent - prev_sent))
	delta_received=$((received - prev_received))
	delta_total=$((total - prev_total))

	difference=$((delta_total - prev_delta_total))
	# echo $delta_total $prev_delta_total $difference
	if [ $difference -gt 10 ]; then
		symbol="+"
	elif [ $difference -lt -10 ]; then
		symbol="-"
	else
		symbol=" "
	fi

	printf "%s  %5d  %5d  %5d  %s\n" "$current_time" "$delta_sent" "$delta_received" "$delta_total" "$symbol"

	prev_sent=$sent
	prev_received=$received
	prev_total=$total

	prev_delta_total=$delta_total
done
