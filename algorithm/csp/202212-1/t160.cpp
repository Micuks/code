#include <iostream>
#include <vector>
using namespace std;
int main() {
    int n;
    double i;
    cin >> n >> i;
    vector<double> income;
    for (int i = 0; i <= n; i++) {
        double tmp;
        cin >> tmp;
        income.push_back(tmp);
    }
    double current = 0;
    double times = 1;
    for (int j = 0; j <= n; j++) {
        auto future = income.at(j);
        current += future * times;
        times /= (1 + i);
    }

    cout << current << endl;

    return 0;
}
