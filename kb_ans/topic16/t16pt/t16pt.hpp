#ifndef _t16pt_20200716_
#define _t16pt_20200716_
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

const int MAXN = 2e6 + 3;

struct trie {
    static const char ori = 'a';
    struct node {
        int num;
        int next[26];
    } data[MAXN];
    int dlen;

    void init()
    {
        memset(this, 0, sizeof(*this));
        dlen = 0;
    }
    void append(const char s[], const int len)
    {
        int now = 0;
        for (int i = 0; i < len; ++i) {
            if (!data[now].next[s[i] - ori]) {
                data[now].next[s[i] - ori] = ++dlen;
            }
            now = data[now].next[s[i] - ori];
        }
        ++data[now].num;
    }
} tt;

char sm[MAXN << 1];
void manacher_init(const char s[], const int len)
{
    sm[0] = '#';
    for (int i = 0; i < len; ++i) {
        sm[(i << 1) + 1] = s[i];
        sm[(i << 1) + 2] = '#';
    }
}
vector<int> manacher(const char s[], int len)
{
    manacher_init(s, len);
    int mx = 0, id = 0;
    len += len + 1;
    vector<int> p(len);
    for (int i = 0; i < len; ++i) {
        if (i < mx) {
            p[i] = min(p[2 * id - i], mx - i);
        }
        else {
            p[i] = 1;
        }

        while (i - p[i] >= 0 && i + p[i] < len && sm[i - p[i]] == sm[i + p[i]]) {
            ++p[i];
        }
        if (mx < i + p[i]) {
            mx = i + p[i];
            id = i;
        }
    }
    return p;
}

char str[MAXN], rev_str[MAXN];
int beg[MAXN];
int slen[MAXN];
int n, offset;

int main(int argc, char **argv)
{
    offset = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
        scanf("%d %s", &slen[i], str + offset);
        beg[i] = offset;
        offset += slen[i];
        tt.append(str + beg[i], slen[i]);
    }
    long long ans = 0;
    for (int i = 0; i < n; ++i) {
        long long c = 0;
        vector<int> m = manacher(str + beg[i], slen[i]);
        int l = slen[i];
        for (int t = l, now = 0; t > 0;) {
            if (m[t] == t + 1) {
                c += tt.data[now].num;
            }
            --t;
            if (t <= 0)
                break;
            now = tt.data[now].next[(str + beg[i])[t] - tt.ori];
            if (!now)
                break;
        }
        ans += c;
    }
    tt.init();
    for (int i = 0; i < n; ++i) {
        strncpy(rev_str, str + beg[i], slen[i]);
        reverse(rev_str, rev_str + slen[i]);
        tt.append(rev_str, slen[i]);
    }
    for (int i = 0; i < n; ++i) {
        long long c = 0;
        vector<int> m = manacher(str + beg[i], slen[i]);
        int l = slen[i];
        for (int t = l, now = 0; t <= m.size();) {
            if (m[t] == m.size() - t)
                c += tt.data[now].num;
            ++t;
            if (t >= m.size())
                break;
            now = tt.data[now].next[(str + beg[i])[t - l - 1] - tt.ori];
            if (!now)
                break;
        }
        ans += c;
    }
    printf("%lld\n", ans);
    return 0;
};

#endif
