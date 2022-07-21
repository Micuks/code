#ifndef _t12pe_20200211_
#define _t12pe_20200211_
#include <algorithm>
#include <assert.h>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <functional>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
#define DEBUG
#ifdef DEBUG
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        cmd;                                                                                       \
    } while (false)
#else
#define DEBUG_CMD(cmd)                                                                             \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)
#endif
#define _DEBUG_CMD(cmd)                                                                            \
    do {                                                                                           \
        ;                                                                                          \
    } while (false)

const int MAXN = 1 << 10;

int numbers[MAXN];
int lis[MAXN];
int acc[MAXN];
int N;

int *first_less_or_eq_than(int *b, int *e, int num)
{
    int *ret = e;
    while (b < e) {
        if (*b <= num) {
            ret = b;
            break;
        }
        else {
            ++b;
        }
    }
    return ret;
}

int main(int argc, char **argv)
{
    long max_lis;
    int num;
    while (cin >> N && N != 0) {
        memset(lis, 0, sizeof(lis));
        memset(acc, 0, sizeof(acc));
        max_lis = 0;
        for (int i = 0; i < N; ++i) {
            scanf("%d", &numbers[i]);
        }
        _DEBUG_CMD({
            cout << "numbers: ";
            for (int j = 0; j < N; ++j) {
                cout << numbers[j] << ' ';
            }
            cout << endl;
        });
        memcpy(acc, numbers, sizeof(acc));
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < i; ++j) {
                if (numbers[j] < numbers[i]) {
                    acc[i] = max(acc[i], acc[j] + numbers[i]);
                }
            }
        }
        /*
        for (int i = 0; i < N; ++i) {
            // int *end = lower_bound(lis, lis + max_lis, numbers[i]);
            num = numbers[i];
            int *end = first_less_or_eq_than(lis + 1, lis + max_lis + 1, num);
            DEBUG_CMD({
                cout << "lis: ";
                for (int j = 0; j < max_lis + 1; ++j) {
                    cout << lis[j] << ' ';
                }
                cout << ", end: " << end - lis << " numbers:[i]: " << numbers[i] << endl;
            });
            _DEBUG_CMD({
                if (N == 5) {
                    cout << "end:" << end << " max_lis: " << max_lis << " num: " << num << endl;
                    cout << "lis: ";
                    for (int j = 0; j < max_lis + 1; ++j) {
                        cout << lis[j] << " ";
                    }
                    cout << endl;
                }
            });
            if (end == lis + max_lis + 1) {
                acc[max_lis + 1] = acc[max_lis] + num;
                lis[max_lis + 1] = num;
                max_lis += 1;
                _DEBUG_CMD({
                    if (N == 5) {
                        cout << "acc[max_lis + 1]: " << acc[max_lis + 1]
                             << " acc[max_lis]: " << acc[max_lis] << " max_lis: " << max_lis
                             << endl;
                    }
                });
            }
            else {
                acc[lis - end] = acc[lis - end] - *end + num;
                *end = num;
            }
            _DEBUG_CMD({
                if (N == 5) {
                    cout << "end:" << end << " max_lis: " << max_lis << " num: " << num << endl;
                    cout << "lis: ";
                    for (int j = 0; j < max_lis + 1; ++j) {
                        cout << lis[j] << " ";
                    }
                    cout << endl;
                }
            });
        }
        */
        _DEBUG_CMD({
            cout << "acc: ";
            for (int i = 0; i <= N; ++i) {
                cout << acc[i] << ", ";
            }
            cout << endl;
            cout << "lis: ";
            for (int i = 0; i <= N; ++i) {
                cout << lis[i] << ", ";
            }
            cout << endl;
        });
        cout << *max_element(acc, acc + N) << endl;
    }
    return 0;
};

#endif
