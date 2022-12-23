import json


def convert(in_filename, out_filename):
    with open(in_filename, 'r') as json_file:
        json_list = json.load(json_file)
        json_formatted_str = json.dumps(
            json_list, indent=4, ensure_ascii=False).encode('utf-8').decode('utf-8')
        # print(json_formatted_str.decode('utf-8'))

    print(f"Converted {len(json_list)} records from file {in_filename}.")

    with open(out_filename, 'w') as json_file:
        json_file.write(json_formatted_str)

    return json_formatted_str


if __name__ == "__main__":
    in_files = ['new_house.json', 'second_hand.json']
    out_files = ['converted_new_house.json', 'converted_second_hand.json']
    json_formatted_str = str()

    for i in range(len(in_files)):
        in_filename = in_files[i]
        out_filename = out_files[i]
        json_formatted_str = convert(in_filename, out_filename)
        # print(json_formatted_str)
