#!/bin/bash

# Create the bing directory if it doesn't exist
mkdir -p bing

# Function to download images
download_image() {
	local p="$0"
	local img_url="$1"
	local date="$2"
	local description="$3"
	local file_name="bing/$date $description.jpg"
	echo "p: $p"
	echo "img_url: $img_url"
	echo "date: $date"
	echo "description: $description"
	echo "file_name: $file_name"

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
	echo ""
}

export -f download_image

# Read the last processed page number from a file, or start from page 1
last_processed_page=1
if [ -f "last_processed_page.conf" ]; then
	last_processed_page=$(cat "last_processed_page.conf")
fi

# Get total pages
main_page_url="https://bing.ioliu.cn/"
content=$(curl -s "$main_page_url")
total_pages=$(echo "$content" | awk '/class="page"/{match($0, /([0-9]+) \/ ([0-9]+)/, a); print a[2]}')

# Iterate through the pages
for p in $(seq "$last_processed_page" "$total_pages"); do
	echo "Downloading images from page $p"
	page_url="https://bing.ioliu.cn/?p=$p"

	# Get the page content and extract the relevant information
	content=$(curl -s "$page_url")
	# content=$(cat './index.html?p=36')

	img_urls=$(echo "$content" | grep -Eo 'data-progressive="https://[^"]*"')
	dates=$(echo "$content" | grep -Eo '<em class="t">[0-9]{4}-[0-9]{2}-[0-9]{2}</em>' | awk -F '[<>]' '{print $3}')
	descriptions=$(echo "$content" | grep -Eo '<h3>[^<]*</h3>' | sed -E 's/<\/?h3>//g' | sed 's/[\/:*?<>|]/_/g')

	# Iterate through the image links, descriptions, and dates
	paste <(echo "$img_urls") <(echo "$dates") <(echo "$descriptions") | while read -r img_url date description; do
		img_url=$(echo "$img_url" | awk -F '"' '{print $2}')
		description=$(echo "$description" | sed 's/<[^>]*>//g' | awk '{$1=$1};1')

		# Launch multiple processed to download images concurrently
		printf '%s\0' "$img_url" "$date" "$description" | xargs -0 -P 5 -n 3 bash -c 'download_image "$@"' _
	done

	# Save the last processed page number to a file
	echo "$p" >"last_processed_page.conf"

	# Sleep for a while to avoid overloading the server
	sleep 10
done

echo "Download completed."
