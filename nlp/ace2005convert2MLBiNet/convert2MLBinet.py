import argparse
import re
import json


def replace_bracket(word: str):
    if word == "(":
        return "-LRB-"
    elif word == ")":
        return "-RRB-"
    elif word == "[":
        return "-LSB-"
    elif word == "]":
        return "-RSB-"
    elif word == "{":
       return "-LCB-"
    elif word=="}":
        return "-RCB-"
    
    return word


def flatten(lists=[]):
    result = []
    for l in lists:
        for i in l:
            if isinstance(i, list):
                result = flatten(l)
                break
            else:
                result = lists
                break

    return result


def get_attributes(
        word_offset: int, ners=[], relations=[], events=[], debug=False):
    # Initialize er, relation and event of word
    word_ner = "O"
    word_relation = "O"
    word_event = "O"

    for lst in ners:
        begin_ner, end_ner, identifier_ner = lst

        if word_offset == begin_ner:
            word_ner = "B-1_"+identifier_ner
            break
        elif begin_ner < word_offset <= end_ner:
            word_ner = "I-1_"+identifier_ner
            break

    for lst in relations:
        offset_pairs = lst[:-1]
        identifier_relation = lst[-1]

        # If relation already found, ignore following relations. Even though
        # they may contaion the word.
        if (word_relation.find("B") == 0) or (word_relation.find("I") == 0):
            break

        # Find word in offset pairs.
        it_pairs = iter(offset_pairs)
        for begin_relation in it_pairs:
            end_relation = next(it_pairs)

            if word_offset == begin_relation:
                word_relation = "B-2_"+identifier_relation
                break
            elif begin_relation < word_offset <= end_relation:
                word_relation = "I-2_"+identifier_relation
                break

    for lst in events:
        # Event in [offset, "str"] format.
        if(isinstance(lst[1], str)):
            offset_event, identifer_event = lst
            if word_offset == offset_event:
                word_event = "B-3_"+identifer_event
        # Event in [offset_begin. offset_end, "str"] format.
        elif(isinstance(lst[2], str)):
            begin_event, end_event, identifer_event = lst
            if word_offset == begin_event:
                word_event = "B-3_"+identifer_event
            elif begin_event < word_offset <= end_event:
                word_event = "I-3_"+identifer_event

    if debug:
        print(f"{word_offset} {word_ner} {word_relation} {word_event}")

    return (word_ner, word_relation, word_event)


def preprocess(process_type, filename, debug=False):
    lines = []

    # Set maximum line limit in case there's something
    # wrong with file input.
    LINE_LIMIT = 1000000

    print("="*20)
    print(f"Preprocessing file {filename} in {process_type} mode...")

    with open(filename, mode='r') as json_file:

        current_document = ""
        # Store output result line by line in list.
        # e.g. lines = ["A B O O O", "C D O O O"]

        while LINE_LIMIT:
            LINE_LIMIT-=1
            # Parse json objects line by line.
            str_jsonobj = json_file.readline()
            if not str_jsonobj:
                break

            if debug:
                print(f"current_line[{1000000-LINE_LIMIT}]: {str_jsonobj}")

            jsonobj = json.loads(str_jsonobj)
            sentence = jsonobj["sentence"]
            s_start = jsonobj["s_start"]
            ner = jsonobj["ner"]
            relation = jsonobj["relation"]
            event = jsonobj["event"]
            event = flatten(event)

            if debug:
                print(f"sentence: {jsonobj['sentence']}")
                print(f"current_document: {current_document}")
                print(f"s_start: {jsonobj['s_start']}")
                print(f"ner: {jsonobj['ner']}")
                print(f"relation: {jsonobj['relation']}")
                print(f"event: {jsonobj['event']}")

            # Assign current document name
            if s_start == 0:
                current_document = sentence[0]
                continue

            for i in range(len(sentence)):
                word_offset = s_start+i
                word = sentence[i]
                word = replace_bracket(word)
                word_ner, word_relation, word_event = get_attributes(
                    word_offset, ner, relation, event, debug)

                list_line = [word, current_document, word_ner, word_relation,
                             word_event]

                # convert list_line to string as a record
                str_line = " ".join(list_line)
                # Append \n to the end of str_line
                str_line += '\n'

                # Append this record to lines.
                lines.append(str_line)

            print("-"*10)

        assert LINE_LIMIT >= 0

    # if debug:
    #     for str in lines:
    #         print(str, end='')

    with open(
            'output/'+re.sub(r'^.*/', '', filename)+'.'+process_type, mode='w') \
            as output_file:
        for str in lines:
            output_file.write(str)

    print("End of processing.")
    print("="*20)


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument(
        '--data',
        help='Path of converted ACE2005 English data in json format.',
        default='./ace-event/dev_convert.json')
    parser.add_argument(
        '--type',
        help='Type of data to be preprocessed. \
                Available types: dev, test, train')
    parser.add_argument(
        '--debug', help='Get more output info for debug purpose.',
        default=False
    )

    args = parser.parse_args()
    filename = args.data
    process_type = args.type
    debug = args.debug

    print(f"filename[{filename}], process_type[{process_type}]")
    preprocess(process_type, filename, debug)
