#include <fstream>
#include <iostream>
#include <random>

using namespace std;
int main(int argc, char *argv[]) {
    random_device mt;
    mt19937 generator(mt());
    uniform_int_distribution<int> Q_distr(0, 255);
    uniform_int_distribution<int> n_distr(1, 64);
    uniform_int_distribution<int> T_distr(0, 2);
    uniform_int_distribution<int> M_distr(-128, 127);

    fstream fs;
    string filename = "in";
    fs.open(filename, ios_base::out);

    auto size = 8;
    for (auto i = 0; i < 8; i++) {
        for (auto j = 0; j < 8; j++) {
            fs << Q_distr(mt) << &" "[(j == 7)];
        }
        fs << endl;
    }

    auto n = n_distr(mt);
    auto T = T_distr(mt);
    fs << n << endl << T << endl;

    for (auto i = 0; i < n; i++) {
        fs << M_distr(mt) << " "[(i == (n - 1))];
    }
    cout << endl;

    fs.close();

    return 0;
}
