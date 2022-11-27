#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

using namespace std;
const int default_amount_of_random_numbers = 50;

class Parser {
  public:
    Parser(int argc, char **argv);
    const int get_range_from() const { return range_from; }
    const int get_range_to() const { return range_to; }
    const int get_amount_of_random_numbers() const {
        return amount_of_random_numbers;
    }

  private:
    int parse_unit_arg(char *single_arg);
    void parse_arg_count_4();
    void parse_arg_count_3();
    void parse_no_arg();
    int argc;
    char **argv;
    int range_from;
    int range_to;
    int amount_of_random_numbers;
};
int Parser::parse_unit_arg(char *single_arg) {
    int x = 0;
    string arg = single_arg;
    try {
        size_t pos;
        x = stoi(arg, &pos);
        if (pos < arg.size()) {
            cerr << "Trailing characters after number: " << arg << "\n";
        }
    } catch (invalid_argument const &e) {
        cerr << "Invalid number: " << arg << "\n";
    } catch (out_of_range const &e) {
        cerr << "Number out of range: " << arg << "\n";
    }
    return x;
}

/**
 * Generate an amount of argv[3] random numbers distributed
 * from argv[1] to argv[2].
 */
void Parser::parse_arg_count_4() {
    range_from = parse_unit_arg(argv[1]);
    range_to = parse_unit_arg(argv[2]);
    amount_of_random_numbers = parse_unit_arg(argv[3]);
}

void Parser::parse_arg_count_3() {
    range_from = parse_unit_arg(argv[1]);
    range_to = parse_unit_arg(argv[2]);
}

Parser::Parser(int argc, char **argv) : argc(argc), argv(argv) {
    if (argc == 4) {
        parse_arg_count_4();
    } else if (argc == 3) {
        parse_arg_count_3();
        amount_of_random_numbers = default_amount_of_random_numbers;
    } else {
        range_from = 0;
        range_to = 1000;
        amount_of_random_numbers = default_amount_of_random_numbers;
    }
}

int main(int argc, char **argv) {
    Parser parser(argc, argv);
    int range_from = parser.get_range_from();
    int range_to = parser.get_range_to();
    int amount_of_random_numbers = parser.get_amount_of_random_numbers();

    random_device rand_dev;
    mt19937 generator(rand_dev());
    uniform_int_distribution<int> distr(range_from, range_to);

    fstream fs;
    string filename = "data/huffman_yasample.in";
    fs.open(filename, ios_base::out);

    vector<int> rawNumbers;
    long long sum = 0;
    // Generate frequencies.
    for (int i = 0; i < amount_of_random_numbers; i++) {
        int tmp = distr(generator);
        rawNumbers.push_back(tmp);
        sum += (long long)tmp;
    }

    if (fs.is_open()) {
        fs << amount_of_random_numbers << std::endl;
        for (int i = 0; i < amount_of_random_numbers; i++) {
            fs << (double)rawNumbers[i] / (double)sum << " ";
        }
        fs << std::endl;
    }
    fs.close();
    return 0;
}
