import json

in_filename = 'new_house.json'
out_filename = 'converted_new_house.json'
json_formatted_str = str()

with open(in_filename, 'r') as json_file:
    json_list = json.load(json_file)
    json_formatted_str = json.dumps(
        json_list, indent=4, ensure_ascii=False).encode('utf-8').decode('utf-8')
    # print(json_formatted_str.decode('utf-8'))

print(f"Converted {len(json_list)} records.")

with open(out_filename, 'w') as json_file:
    json_file.write(json_formatted_str)
