#include <fstream>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char **argv) {
    random_device rand_dev;
    mt19937 generator(rand_dev());

    uniform_int_distribution<int> n_generate(1, 10);
    uniform_int_distribution<int> distr(0, 2e4);

    fstream fs;
    string filename = "in";

    int n = n_generate(generator);

    fs.open(filename, ios_base::out);
    if (fs.is_open()) {
        fs << n << endl;
        for (int i = 0; i < n; i++) {
            fs << distr(generator) << " ";
        }
    }
    fs << endl;
}
