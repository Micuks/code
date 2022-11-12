import argparse
import json


def preprocess(process_type, filename, debug=False):
    result = []
    print("="*20)
    print(f"Preprocessing file {filename} in {process_type} mode...")
    with open(filename, mode='r') as json_file:

        # Set maximum line limit in case there's something
        # wrong with file input.
        LINE_LIMIT = 1000000

        current_document = str()
        # Store output result line by line in list.
        # e.g. lines = ["A B O O O", "C D O O O"]
        lines = []

        while --LINE_LIMIT:
            # Parse json objects line by line.
            str_jsonobj = json_file.readline()
            if not str_jsonobj:
                break

            if debug:
                print(f"sentence: {str_jsonobj}")

            jsonobj = json.loads(str_jsonobj)
            sentence = jsonobj["sentence"]
            s_start = jsonobj["s_start"]
            ner = jsonobj["ner"]
            relation = jsonobj["relation"]
            event = jsonobj["event"]

            if debug:
                print(f"sentence: {jsonobj['sentence']}")
                print(f"s_start: {jsonobj['s_start']}")
                print(f"ner: {jsonobj['ner']}")
                print(f"relation: {jsonobj['relation']}")
                print(f"event: {jsonobj['event']}")

            # Assign current document name
            if s_start == 0:
                current_document = sentence
                continue

            for i in len(sentence):
                word_offset = s_start+i
                word = sentence[i]
                word_ner, word_relation, word_event = \
                    get_attributes(word_offset, ner, relation, event)
                # TODO: Implement get_attributes.
                # ner, ralation and event may be more than one tokens.
                # The first token is B-${TOKEN}, following tokens are
                # I-${TOKEN}.
                # If list is empty, for example, len(event) = 0, then
                # return 'O'.

                if debug:
                    print(f"word_offset: {word_offset}, word_ner: {word_ner},\
                            word_relation: {word_relation}, word_event:\
                          {word_event}")

                list_line = [word, current_document, word_ner, word_relation,
                             word_event]

                # convert list_line to string as a record
                str_line = " ".join(list_line)
                # Append \n to the end of str_line
                str_line += '\n'

                # Append this record to lines.
                lines.append(str_line)

        assert LINE_LIMIT == 0

    if debug:
        for str in lines:
            print(str, end='')

    with open('output/filename.'+process_type, mode='w') as output_file:
        output_file.write(str for str in lines)

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
        '--debug", help="Get more output info for debug purpose.',
        default=False
    )

    args = parser.parse_args()
    filename = args.data
    process_type = args.type

    print(f"filename[{filename}], process_type[{process_type}]")
    preprocess(process_type, filename)
