#include <algorithm>
#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

const int N = 8;

int n, T;

int a[N][N], M[N][N], M1[N][N];
double M2[N][N];
int q[64];

double trans(double i, double j) {
    double res = 0;
    for (int u = 0; u <= 7; u++)
        for (int v = 0; v <= 7; v++)
            if (u == 0 && v == 0)
                res += (double)M1[u][v] * cos(0) * cos(0) / 2.0;
            else if (u == 0)
                res += (double)M1[u][v] * sqrt(0.5) *
                       cos(acos(-1) * (i + 0.5) * double(u) / 8.0) *
                       cos(acos(-1) * (j + 0.5) * v / 8.0);
            else if (v == 0)
                res += (double)M1[u][v] * sqrt(0.5) *
                       cos(acos(-1) * (i + 0.5) * double(u) / 8.0) *
                       cos(acos(-1) * (j + 0.5) * v / 8.0);
            else
                res += (double)M1[u][v] *
                       cos(acos(-1) * (i + 0.5) * double(u) / 8) *
                       cos(acos(-1) * (j + 0.5) * double(v) / 8.0);

    return (double)res / 4.0;
}

int main() {
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            cin >> a[i][j];

    cin >> n >> T;

    for (int i = 0; i < n; i++)
        cin >> q[i];

    // T1.
    int k = 0;
    for (int i = 0; i < 8; i++)
        if (i % 2 == 0) {
            for (int j = 0; j <= i; j++)
                M[i - j][j] = q[k++];
        } else
            for (int j = 0; j <= i; j++)
                M[j][i - j] = q[k++];

    for (int i = 8; i < 15; i++)
        if (i % 2 == 0)
            for (int j = i - 7; j <= 7; j++)
                M[i - j][j] = q[k++];
        else
            for (int j = i - 7; j <= 7; j++)
                M[j][i - j] = q[k++];

    // T2.
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
            M1[i][j] = M[i][j] * a[i][j];

    // T3.
    for (int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++) {
            M2[i][j] = round(trans(i, j) + 128);
            if (M2[i][j] > 255)
                M2[i][j] = 255;
            if (M2[i][j] < 0)
                M2[i][j] = 0;
        }

    // 输出
    if (T == 0)
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                cout << M[i][j] << " ";
            cout << endl;
        }

    if (T == 1)
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                cout << M1[i][j] << " ";
            cout << endl;
        }

    if (T == 2)
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++)
                cout << M2[i][j] << " ";
            cout << endl;
        }
    return 0;
}
