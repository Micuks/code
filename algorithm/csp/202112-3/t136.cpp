// #define DEBUG
#include <cmath>
#include <exception>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
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
            } else if (isnumber(a)) {
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
            } else if (isnumber(a)) {
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
            } else if (isnumber(a)) {
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

    for (auto &a : data) {
        cout << a << " ";
    }
    cout << endl;

    return 0;
}
