#include <fstream>
#include <iostream>
#include <random>
using namespace std;
int main(int argc, char *argv[]) {
    random_device rand_dev;
    mt19937 mt(rand_dev());

    uniform_real_distribution<double> doub_distr(-1e5, 1e5);
    uniform_int_distribution<int> int_distr(0, 1e3);

    fstream fs;
    string filename = "in";
    fs.open(filename, ios_base::out);
    assert(fs.is_open());

    int N, S, P, T;
    int rn;
    double v0, u0, a, b, c, d;
    int r;
    int ss, tt, dd;
    double ww;
    double dt = 0.1;

    N = int_distr(mt);
    S = int_distr(mt);
    P = int_distr(mt);
    T = int_distr(mt);

    fs << N << " " << S << " " << P << " " << T << endl;
    fs << dt << endl;
    rn = int_distr(mt);
    while (N > rn) {
        v0 = doub_distr(mt);
        u0 = doub_distr(mt);
        a = doub_distr(mt);
        b = doub_distr(mt);
        c = doub_distr(mt);
        d = doub_distr(mt);
        cout << rn << " " << v0 << " " << u0 << " " << a << " " << b << " " << c
             << " " << d << endl;
        N -= rn;
    }
    v0 = doub_distr(mt);
    u0 = doub_distr(mt);
    a = doub_distr(mt);
    b = doub_distr(mt);
    c = doub_distr(mt);
    d = doub_distr(mt);
    cout << N << " " << v0 << " " << u0 << " " << a << " " << b << " " << c
         << " " << d << endl;

    for (int i = 0; i < P; i++) {
        r = int_distr(mt);
        cout << r << endl;
    }

    for (int i = 0; i < S; i++) {
        ss = int_distr(mt);
        tt = int_distr(mt);
    }

    return 0;
}
