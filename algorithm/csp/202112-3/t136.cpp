// #define DEBUG
#include <algorithm>
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MOD = 929;
vector<int> generateG(int k);

int main() {
    int w, s;
    cin >> w >> s;
    string str;
    vector<int> data;
    vector<int> tmpData;

    int k = (s == -1) ? 0 : pow(2, s + 1);

    data.push_back(0); // Indicates length of data module
    getchar();
    getline(cin, str);

#ifdef DEBUG
    cout << "w[" << w << "]"
         << ", s[" << s << "]"
         << ", k[" << k << "]" << endl;
    cout << "str: " << str << endl;
#endif                     // DEBUG
    int current_state = 0; // 0-Uppercase 1-Lowercase 2-Numeric
    for (auto a : str) {
        switch (current_state) {
        case 0:
            if (isupper(a)) {
                tmpData.push_back(a - 'A');
            } else if (islower(a)) {
                tmpData.push_back(27);
                tmpData.push_back(a - 'a');

                current_state = 1;
            } else if (isdigit(a)) {
                tmpData.push_back(28);
                tmpData.push_back(a - '0');

                current_state = 2;
            } else {
                throw "Invalid input.";
            }
            break;
        case 1:
            if (isupper(a)) {
                tmpData.push_back(28);
                tmpData.push_back(28);
                tmpData.push_back(a - 'A');

                current_state = 0;
            } else if (islower(a)) {
                tmpData.push_back(a - 'a');
            } else if (isdigit(a)) {
                tmpData.push_back(28);
                tmpData.push_back(a - '0');

                current_state = 2;
            } else {
                throw "Invalid input.";
            }
            break;
        case 2:
            if (isupper(a)) {
                tmpData.push_back(28);
                tmpData.push_back(a - 'A');

                current_state = 0;
            } else if (islower(a)) {
                tmpData.push_back(27);
                tmpData.push_back(a - 'a');

                current_state = 1;
            } else if (isdigit(a)) {
                tmpData.push_back(a - '0');
            } else {
                throw "Invalid input.";
            }
            break;
        }
    }
    if (tmpData.size() & 1) {
        tmpData.push_back(29);
    }

    for (auto it = tmpData.begin(); it < tmpData.end(); it += 2) {
        data.push_back((*it) * 30 + *(it + 1));
    }
    while ((data.size() + k) % w) {
        data.push_back(900);
    }
    data[0] = data.size();
    // End of data module

    // Beginning of check module
    vector<int> checkData;

    // Calculate g(x)
    vector<int> g = generateG(k);

#ifdef DEBUG
    cout << "g(x): ";
    for (auto &a : g) {
        cout << a << ' ';
    }
    cout << endl;

    cout << "d(x): ";
    for (auto &a : data) {
        cout << a << " ";
    }
    cout << endl;
#endif // DEBUG

    // Power d(x) by k order
    vector<int> d;
    for (auto &a : data) {
        d.push_back(a);
    }
    for (int i = 0; i < k; i++) {
        d.push_back(0);
    }

    // Calculate r(x)
    int lenD = d.size();
    int lenG = g.size();
    for (int i = 0; i <= lenD - lenG; i++) {
        int a = d.at(i) / g.at(0);
        for (int j = i; j < i + lenG; j++) {
            d.at(j) -= a * g.at(j - i);
        }
    }

    vector<int> r;
    for (int i = 0; i < k; i++) {
        r.push_back(*(d.end() - k + i));
    }

    for (auto &a : r) {
        a = -a;
    }

    // Get mod of r(x)
    for (auto &a : r) {
        a = ((a % MOD) + MOD) % MOD;
    }

    // Append r(x) to end of Data
    for (auto &a : r) {
        data.push_back(a);
    }

#ifdef DEBUG
    // Print r(x)
    cout << "r(x): ";
    for (auto &a : r) {
        cout << a << " ";
    }
    cout << endl;

#endif // DEBUG

    // Answer output
    for (auto &a : data) {
        cout << a << endl;
    }

    return 0;
}

vector<int> generateG(int k) {
    vector<int> g;
    for (int i = 0; i <= k; i++) {
        g.push_back(1);
    }
    try {
        for (int i = 1; i <= k; i++) {
            g.at(i) = 1;
            for (int j = i - 1; j > 0; j--) {
                g.at(j) = g.at(j - 1) - pow(3, i) * g.at(j);
            }
            g.at(0) = g.at(0) * -pow(3, i);
        }
    } catch (exception &e) {
        cout << "ERROR: " << e.what() << endl;
    }

    // for (auto &a : g) {
    //     a = (a + MOD) % MOD;
    // }

    reverse(g.begin(), g.end());
    return g;
}
