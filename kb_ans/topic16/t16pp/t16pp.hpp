#ifndef _t16pp_20200715_
#define _t16pp_20200715_
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

typedef long long LL;
typedef std::pair<LL, LL> pll_type;
std::set<pll_type> min_set;
const int MAXN = 1e4 + 7;
int n;
char bead[1 << 8];
int blen;

std::ostream &operator<<(std::ostream &os, pll_type const &p)
{
    os << "first: " << p.first << " second: " << p.second;
    return os;
}

int get_min_representation()
{
    int i = 0, j = 1;
    while (i < blen && j < blen) {
        int k = 0;
        while (k < blen && bead[i + k] == bead[j + k])
            ++k;
        if (k >= blen)
            break;
        if (bead[i + k] > bead[j + k]) {
            i += k + 1;
        }
        else {
            j += k + 1;
        }
        if (i == j) {
            ++j;
        }
    }
    return min(i, j);
}

pll_type get_pair_representation(const char *str, int slen)
{
    string s(str, slen);
    LL pfirst, psecond;
    pfirst = psecond = 0;
    size_t ssize = s.size();
    string sfirst = ssize > 64 ? s.substr(0, ssize - 64) : "";
    string ssecond = ssize <= 64 ? s : s.substr(ssize - 64, 64);

    _DEBUG_CMD(cout << "sfirst: " << sfirst << " ssecond: " << ssecond << " sfirst.size(): "
                    << sfirst.size() << " ssecond.size(): " << ssecond.size() << endl);

    for (int i = 0; i < sfirst.size(); ++i) {
        pfirst = ((pfirst << 1) | (sfirst[i] == '0' ? 0 : 1));
    }
    for (int i = 0; i < ssecond.size(); ++i) {
        psecond = ((psecond << 1) | (ssecond[i] == '0' ? 0 : 1));
    }
    return pll_type(pfirst, psecond);
}

int main(int argc, char **argv)
{
    while (~scanf("%d", &n)) {
        min_set.clear();
        for (int i = 0; i < n; ++i) {
            scanf("%s", bead);
            blen = strlen(bead);
            strncpy(bead + blen, bead, blen);
            int min_offset = get_min_representation();
            _DEBUG_CMD(cout << "min_offset: " << min_offset << " str before shift: " << bead);
            for (int i = 0; i < blen; ++i) {
                bead[i] = bead[i + min_offset];
            }
            _DEBUG_CMD(cout << " str after shifted: " << bead << endl;);
            pll_type p = get_pair_representation(bead, blen);
            _DEBUG_CMD({ cout << p << endl; });
            min_set.insert(p);
        }
        printf("%lu\n", min_set.size());
    }
    return 0;
};

#endif
