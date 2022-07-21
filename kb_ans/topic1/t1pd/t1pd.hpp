#ifndef _t1pd_20191204_
#define _t1pd_20191204_
#include <algorithm>
#include <assert.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <vector>
using namespace std;

int M, N;
int tiles[32][32];
int tramp[32][32];
int best_tramp[32][32];
int best_step = 100000;

void flip(int m, int n)
{
    int offsets[][2] = {{0, 0}, {0, 1}, {1, 0}, {0, -1}, {-1, 0}};
    for (int i = 0; i < 5; ++i) {

        int newm = m + offsets[i][0];
        int newn = n + offsets[i][1];
        if (newm >= 0 && newm < M && newn >= 0 && newn < N) {
            tiles[newm][newn] = tiles[newm][newn] == 1 ? 0 : 1;
        }
    }
}

bool all_of(int *b, int *e, bool (*f)(int x))
{
    while (b != e) {
        if (not f(*b))
            return false;
        b = b + 1;
    }
    return true;
}

bool f(int x) { return x == 0; }
void dfs(int start_pos)
{
    int total_step = 0;
    for (int i = 0; i < N; ++i) {
        tramp[0][N - i - 1] = ((start_pos >> i) & 0x1);
        if (tramp[0][N - i - 1]) {
            total_step += 1;
            flip(0, N - i - 1);
        }
    }
    for (int i = 1; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tiles[i - 1][j]) {
                tramp[i][j] = 1;
                total_step += 1;
            }
        }
        for (int j = 0; j < N; ++j) {
            if (tramp[i][j]) {
                flip(i, j);
            }
        }
    }
    if (all_of(tiles[M - 1], tiles[M - 1] + N, f) && total_step < best_step) {
        best_step = total_step;
        memcpy(best_tramp, tramp, sizeof(int) * 32 * 32);
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            if (tramp[i][j] == 1)
                flip(i, j);
        }
    }
    return;
}

int main(int argc, char **argv)
{
    cin >> M >> N;
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < N; ++j) {
            cin >> tiles[i][j];
        }
    }
    memset(best_tramp, 0, sizeof(int) * 32 * 32);
    for (int i = 0; i < (1 << N); ++i) {
        memset(tramp, 0, sizeof(int) * 32 * 32);
        dfs(i);
    }
    if (best_step != 100000) {
        for (int i = 0; i < M; ++i) {
            for (int j = 0; j < N; ++j) {
                if (j != N - 1)
                    cout << best_tramp[i][j] << ' ';
                else
                    cout << best_tramp[i][j] << endl;
            }
        }
        return 0;
    }
    cout << "IMPOSSIBLE" << endl;
    return 0;
};

#endif
