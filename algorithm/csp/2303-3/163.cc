#include <algorithm>
#include <bitset>
#include <cctype>
#include <ios>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// #define debug

#ifdef debug
#define deb(x...)                                                              \
  cout << #x << " =[";                                                         \
  _print(x)
#else
#define deb(x...)
#endif

void __print(int a) { cout << a; }
void __print(char a) { cout << a; }
void __print(double a) { cout << a; }
void __print(size_t a) { cout << a; }
void __print(const string &a) { cout << a; }
void __print(const char *x) { cout << x; }
template <typename T> void __print(const T &a) {
  int f = 0;
  cout << '{';
  for (auto &i : a) {
    cout << (f++ ? "," : ""), __print(i);
  }
  cout << '}';
}
void _print() { cout << ']' << endl; }
template <typename T, typename... V> void _print(T x, V... y) {
  __print(x);
  if (sizeof...(y))
    cout << ", ";
  _print(y...);
}
struct hash_pair {
  template <class T1, class T2> size_t operator()(const pair<T1, T2> &p) const {
    auto h1 = hash<T1>{}(p.first);
    auto h2 = hash<T2>{}(p.second);
    if (h1 != h2) {
      return h1 ^ h2;
    }
    return h1;
  }
};

typedef long long ll;
typedef pair<int, int> Pint;
typedef vector<int> Vint;
const int N = 2502;
unordered_map<Pint, Vint, hash_pair> mKv;
unordered_map<int, Vint> mHas;
char op[N];
int n;
// depth
int dn[N];
int num[N];
bitset<N> stk[N];

int main() {
  cin >> n;
  for (int i = 0; i < n; i++) {
    int id, m;
    cin >> id >> m;
    dn[i] = id;
    for (int j = 0; j < m; j++) {
      int k, v;
      cin >> k >> v;
      mHas[k].push_back(i);
      mKv[Pint(k, v)].push_back(i);
    }
  }

  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    int c = -1;
    int d = -1;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string s;
    cin >> s;
    deb(s);
    for (int j = 0; j < s.size();) {
      auto t = s.at(j);
      if (t == '&' || t == '|') {
        op[++c] = t;
        j++;
      } else if (t == '(') {
        j++;
      } else if (t == ')') {
        num[c]++;
        if (num[c] == 2) {
          d--;
          if (op[c] == '&') {
            stk[d] = stk[d] & stk[d + 1];
          } else if (op[c] == '|') {
            stk[d] = stk[d] | stk[d + 1];
          } else {
            throw runtime_error("Invalid operator: " + to_string(op[c]));
          }
          auto printBitset = [&](bitset<N> &bs) -> void {
            for (size_t iter = 0; iter < bs.size(); iter++) {
              if (stk[d].test(iter)) {
                cout << iter << ", ";
              }
            }
            cout << endl;
          };

          deb(c, op[c]);
#ifdef debug
          cout << "stk[" << d << "]: ";
          printBitset(stk[d]);
          cout << "stk[" << d + 1 << "]: ";
          printBitset(stk[d + 1]);
#endif

          num[c--] = 0;
        }
        j++;
      } else {
        int l = 0, r = 0;
        while (isdigit(t = s.at(j))) {
          l = l * 10 + (t - '0');
          j++;
        }
        char mode = t;
        j++;
        while (j < s.size() && isdigit(t = s.at(j))) {
          r = r * 10 + (t - '0');
          j++;
        }

        d++;
        if (mode == ':') {
          auto dns = mKv[Pint(l, r)];
          stk[d].reset();
          for (int k = 0; k < dns.size(); k++) {
            stk[d].set(dns.at(k));
          }
        } else if (mode == '~') {
          auto dnHas = mHas[l];
          auto dnKv = mKv[Pint(l, r)];
          stk[d].reset();
          for (auto &item : dnKv) {
            stk[d].set(item);
          }
          for (auto &item : dnHas) {
            stk[d].flip(item);
          }
        } else {
          throw runtime_error("Invalid mode: " + to_string(mode));
        }
      }
    }

    vector<int> ids;
    for (int j = 0; j < n; j++) {
      if (stk[0].test(j)) {
        ids.push_back(dn[j]);
      }
    }

    sort(ids.begin(), ids.end(), [](int a, int b) -> bool { return a < b; });

    for (auto &id : ids) {
      cout << id << " ";
    }
    cout << endl;
  }

  return 0;
}