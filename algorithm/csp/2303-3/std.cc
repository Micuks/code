#include <algorithm>
#include <bitset>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <cstring>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
typedef long long ll;
typedef pair<int, int> P;
const int N = 2502;
int n, m, sz, id, k, c, d, x, y, num[N], to[N], f[N];
map<int, int> q[N];
map<P, vector<int>> p;
map<int, vector<int>> has;
char s[N], op[N];
bitset<N> stk[N * 2], res;
bitset<N> cal(int l, char x, int r) {
    bitset<N> ans;
    for (auto &v : p[P(l, r)]) {
        ans.set(v);
    }
    if (x == '~') {
        for (auto &v : has[l]) {
            ans.flip(v);
        }
    }
    return ans;
}
int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
        scanf("%d%d", &id, &k);
        to[i] = id;
        for (int j = 1; j <= k; ++j) {
            scanf("%d%d", &x, &y);
            q[i][x] = y;
            has[x].push_back(i);
            p[P(x, y)].push_back(i);
        }
    }
    scanf("%d", &m);
    for (int i = 1; i <= m; ++i) {
        scanf("%s", s);
        sz = strlen(s);
        c = d = 0;
        for (int j = 0; j < sz;) {
            if (s[j] == '&' || s[j] == '|') {
                op[++c] = s[j++];
            } else if (s[j] == '(') {
                j++;
            } else if (s[j] == ')') {
                num[c]++;
                if (num[c] == 2) {
                    d--;
                    if (op[c] == '&')
                        stk[d] = stk[d] & stk[d + 1];
                    else
                        stk[d] = stk[d] | stk[d + 1];
                    num[c--] = 0;
                }
                j++;
            } else {
                int cur = j, l = 0, r = 0;
                while (cur < sz && (s[cur] != ':' && s[cur] != '~')) {
                    l = l * 10 + (s[cur] - '0');
                    cur++;
                }
                char x = s[cur++];
                while (cur < sz && s[cur] != ')') {
                    r = r * 10 + (s[cur] - '0');
                    cur++;
                }
                stk[++d] = cal(l, x, r);
                j = cur;
            }
        }
        int e = 0;
        for (int j = 1; j <= n; ++j) {
            if (stk[d].test(j)) {
                f[++e] = to[j];
            }
        }
        sort(f + 1, f + e + 1);
        for (int j = 1; j <= e; ++j) {
            printf("%d%c", f[j], " \n"[j == e]);
        }
        if (!e)
            puts("");
    }
    return 0;
}
