#!/bin/bash

# Create the bing directory if it doesn't exist
mkdir -p bing

# Function to download images
download_image() {
	local p="$1"
	local img_url="$2"
	local date="$3"
	local description="$4"
	local file_name="bing/$date $description.jpg"

	# Check if the image has been downloaded
	if [ ! -f "$file_name" ]; then
		local tmp_file="$file_name.$$" # use a temporary file with PID to avoid conflicts
		echo "Downloading '$file_name'"
		if wget -q -O "$tmp_file" "$img_url"; then
			mv "$tmp_file" "$file_name" # Rename the temporary file if the download is successful
		else
			rm "$tmp_file" # Remove the temporary file if the download fails
		fi
	fi
}

export -f download_image

# Iterate through the pages
for p in {1..128}; do
	echo "Downloading images from page $p"
	page_url="https://bing.ioliu.cn/?p=$p"

	# Get the page content and extract the relevant information
	content=$(curl -s "$page_url")

	img_urls=$(echo "$content" | grep -Eo 'date-progressive="https://[^"]*"')
	dates=$(echo "$content" | grep -Eo '<em class="t">[0-9]{4}-[0-9]{2}-[0-9]{2}</em>')
	descriptions=$(echo "content" | grep -Eo '<h3>[^<]*</h3>' | sed 's/[\/:*?<>|]/_/g')

	# Iterate through the image links, descriptions, and dates
	paste <(echo "$img_urls") <(echo "$dates") <(echo "$descriptions") | while read -r img_url date description; do
		img_url=$(echo "$img_url" | awk -F '"' '{print $2}')
		date=$(echo "$date" | awk -F '"' '{print $3}')
		description=$(echo "$description" | sed 's/<[^>]*>//g' | awk '{$1=$1};1')

		# Launch multiple processed to download images concurrently
		printf '%s\0' "$img_url" "$date" "$description" | xargs -0 -P 5 -n 3 bash -c 'download_image "$@"' _
	done

	# Sleep for a while to avoid overloading the server
	sleep 10
done

echo "Download completed."
