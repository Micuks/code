#include "CLIParser.hpp"
#include <algorithm>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

string CLIParser::helpStr() {
    int width = 5;
    string help = "--help";
    string in = "--in <filename>";
    string out = "--out <filename>";
    vector<size_t> arg_lengths;
    arg_lengths.push_back(help.length());
    arg_lengths.push_back(in.length());
    arg_lengths.push_back(out.length());

    string inDesc = "Input filename.";
    string outDesc = "Output filename.";

    width = *max_element(arg_lengths.begin(), arg_lengths.end()) + 5;
    stringstream ss;
    ss << "Usage: ./Kruskal [--help] [--in <filename>] [--out <filename>]\n"
       << left << setw(width) << help << endl
       << left << setw(width) << in << inDesc << endl
       << left << setw(width) << out << outDesc << endl;

    return ss.str();
}

// Hash args to hashmap in (key, value) format.
void CLIParser::hashArgs() {
    if ((argc >= 1) && (argc & 1)) {
        for (int i = 0; i < argc / 2; i++) {
            int key = i * 2 + 1;
            int val = i * 2 + 2;
            args[argv[key]] = argv[val];
        }
    } else if (argc == 2) {
        if (string(argv[1]) == string("--help")) {
            cout << helpStr();
            exit(0);
        }
    } else {
        throw invalid_argument("ERROR: Invalid argument. ALl args passed "
                               "should be in --key value format.\n" +
                               helpStr());
    }
}

void CLIParser::argParse() {
    // If no input and output file specified. Use default input and output
    // file.
    // Else parse and save args to hashmap.
    if (argc >= 1) {
        hashArgs();
    } else {
        cout << helpStr();
        exit(0);
    }
}
