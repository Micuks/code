#include <fstream>
#include <iostream>
#include <random>

using namespace std;
int main(int argc, char *argv[]) {
    random_device mt;
    mt19937 generator(mt());
    uniform_int_distribution<int> n_distr(1, 16);
    uniform_int_distribution<int> k_distr(1, 5);
    uniform_int_distribution<int> p_distr(1, 1e4);

    fstream fs;
    string filename = "in";

    int n = n_distr(mt);
    int k = k_distr(mt);
    cout << "n[" << n << "], k[" << k << "]" << endl;
    long long sum_p = 0;
    vector<int> ps;
    for (int i = 0; i < n; i++) {
        int p = p_distr(mt);
        cout << p << " ";

        ps.push_back(p);
        sum_p += p;
    }
    cout << endl;

    double real_sum_p = 0;
    fs.open(filename, ios_base::out);
    fs << n << " " << k << endl;
    for (auto &p : ps) {
        double realp = static_cast<double>(p) / static_cast<double>(sum_p);
        fs << realp << " ";
        real_sum_p += realp;
    }
    fs << endl;
    fs.close();
    cout << "[data_gen] " << real_sum_p << endl;

    return 0;
}
