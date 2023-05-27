#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#define debug

#ifdef debug
#include "debug.hh"
#else
#define deb(x...)
#endif

using namespace std;

class User {
  public:
    User(int dn, int num_attrs) : dn_(dn), num_attrs_(num_attrs) {}

    int dn_;
    int num_attrs_;
    unordered_map<int, int> attrs_;
};

class Solution {
  public:
    void AddUser(shared_ptr<User> u) { dn_to_users_.insert({u->dn_, u}); }
    void AddAttrKeyToDNMap(int attr_key, int dn) {
        attr_key_to_users[attr_key].push_back(dn);
    }
    char GetNextToken(const string &s, size_t &pos);
    vector<int> ParseExpr(const string &expr);
    vector<int> ParseBaseExpr(const string &expr);

    void InitCorrespondingDns() { corresponding_dns_.clear(); }
    const string CorrespondingDn() {
        stringstream ss;
        sort(corresponding_dns_.begin(), corresponding_dns_.end());
        for (auto &dn : corresponding_dns_) {
            ss << dn << ' ';
        }
        ss << endl;
        return ss.str();
    }

    vector<int> PositiveFetchDns(int key, int value);
    vector<int> NegativeFetchDns(int key, int value);

    vector<int> AndExprs(vector<int> dns_a, vector<int> dns_b);
    vector<int> OrExprs(vector<int> dns_a, vector<int> dns_b);

    int n, m;
    unordered_map<int, vector<int>> attr_key_to_users;
    unordered_map<int, shared_ptr<User>> dn_to_users_;

    // temporary
    vector<int> corresponding_dns_;
};

vector<int> Solution::AndExprs(vector<int> dns_a, vector<int> dns_b) {
    vector<int> in;
    set_intersection(dns_a.begin(), dns_a.end(), dns_b.begin(), dns_b.end(),
                     back_inserter(in));

    return in;
}

vector<int> Solution::OrExprs(vector<int> dns_a, vector<int> dns_b) {
    vector<int> un;
    std::set_union(dns_a.begin(), dns_a.end(), dns_b.begin(), dns_b.end(),
                   back_inserter(un));

    return un;
}

vector<int> Solution::PositiveFetchDns(int key, int value) {
    vector<int> dns;
    vector<int> users;
    try {
        users = attr_key_to_users.at(key);
        for (auto &dn : users) {
            auto user = dn_to_users_.at(dn);
            auto user_val = user->attrs_.at(key);
            if (user_val == value)
                dns.push_back(dn);
        }
    } catch (exception e) {
        deb(e.what());
    }

    return dns;
}

vector<int> Solution::NegativeFetchDns(int key, int value) {
    vector<int> dns;
    vector<int> users;

    try {
        users = attr_key_to_users.at(key);
        for (auto &dn : users) {
            auto user = dn_to_users_.at(dn);
            auto user_val = user->attrs_.at(key);
            if (user_val != value)
                dns.push_back(dn);
        }
    } catch (exception e) {
        deb(e.what());
    }

    return dns;
}

char Solution::GetNextToken(const string &s, size_t &pos) {
    return pos < s.size() ? s.at(pos++) : '\0';
}

vector<int> Solution::ParseExpr(const string &expr) {
    vector<char> opers;
    vector<vector<int>> dns;
    int c = 0, d = 0;

    for (size_t i = 0; i < expr.size();) {
        auto t = expr.at(i);
        deb(i, t);
        if (t == '|') {
            opers.push_back('|');
            i++;
        } else if (t == '&') {
            opers.push_back('&');
            i++;
        } else if (t == '(') {
            c++;
            int l = 0;
            while (isdigit(t = expr.at(++i))) {
                l = l * 10 + (t - '0');
            }
            auto mode = t;
            int r = 0;
            while (isdigit(t = expr.at(++i))) {
                r = r * 10 + (t - '0');
            }
            if (mode == ':')
                dns.push_back(PositiveFetchDns(l, r));
            else if (mode == '~')
                dns.push_back(NegativeFetchDns(l, r));
            // Now, t == ')'
        } else if (t == ')') {
            d++;
            if (d == 2) {
                auto oper = opers.back();
                opers.pop_back();
                auto r = dns.back();
                dns.pop_back();
                auto l = dns.back();
                dns.pop_back();

                vector<int> vr;
                if (oper == '&') {
                    set_intersection(l.begin(), l.end(), r.begin(), r.end(),
                                     back_inserter(vr));

                } else if (oper == '|') {
                    set_union(l.begin(), l.end(), r.begin(), r.end(),
                              back_inserter(vr));
                }
                dns.push_back(vr);
                d = 0;
                c -= 2;
            }
            i++;
        } else {
            ParseBaseExpr(expr);
        }
    }
    return dns.back();
}

vector<int> Solution::ParseBaseExpr(const string &expr) {
    char t;
    int l = 0;
    int r = 0;
    int i = -1;
    while (isdigit((t = expr.at(++i)))) {
        l = 10 * l + (t - '0');
    }
    char mode = t;
    while (isdigit((t = expr.at(++i)))) {
        r = 10 * r + (t - '0');
    }

    if (mode == ':') {
        return PositiveFetchDns(l, r);
    } else if (mode == '~') {
        return NegativeFetchDns(l, r);
    } else {
        throw runtime_error("Error: invalid mode: " + to_string(mode));
    }
}

int main() {
    Solution s;
    cin >> s.n;
    // Read users
    for (int i = 0; i < s.n; i++) {
        int dn, k;
        cin >> dn >> k;
        auto u = make_shared<User>(dn, k);
        int l, r;
        for (int j = 0; j < k; j++) {
            cin >> l >> r;
            u->attrs_.insert({l, r});
            s.AddAttrKeyToDNMap(l, dn);
        }
        s.AddUser(u);
    }

    // Read exprs
    cin >> s.m;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    string expr;
    // getline(cin, expr);
    for (int i = 0; i < s.m; i++) {
        // Initialization
        s.InitCorrespondingDns();

        getline(cin, expr);
        s.corresponding_dns_ = s.ParseExpr(expr);
        cout << s.CorrespondingDn();
    }

    return 0;
}
