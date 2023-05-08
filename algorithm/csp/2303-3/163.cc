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

// #define debug

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
    vector<int> ParseExpr(const string &expr, size_t &pos, char &token);
    vector<int> ParseBaseExpr(const string &expr, size_t &pos, char &token);

    void InitCorrespondingDns() { corresponding_dns_.clear(); }
    const string CorrespondingDn() {
        stringstream ss;
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
    } catch (exception e) {
        deb(e.what());
    }
    users = attr_key_to_users.at(key);
    for (auto &dn : users) {
        auto user = dn_to_users_.at(dn);
        if (!user)
            throw runtime_error("Expected user " + to_string(dn));
        auto user_val = user->attrs_.at(key);
        if (!user_val)
            throw runtime_error("Expected value of user " + to_string(dn) +
                                "'s attribute " + to_string(key));
        if (user_val == value)
            dns.push_back(dn);
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
            if (!user)
                throw runtime_error("Expected user" + to_string(dn));
            auto user_val = user->attrs_.at(key);
            if (!user_val)
                throw runtime_error("Expected value of user " + to_string(dn) +
                                    "'s attribute " + to_string(key));
            if (user_val != value)
                dns.push_back(dn);
        }
    } catch (exception e) {
        deb(e.what();)
    }

    return dns;
}

char Solution::GetNextToken(const string &s, size_t &pos) {
    // while (pos < s.size() && isspace(s.at(pos)))
    //     ++pos;
    return pos < s.size() ? s.at(pos++) : '\0';
}

vector<int> Solution::ParseExpr(const string &expr, size_t &pos, char &token) {
    vector<int> dns;
    char mode;

    switch (token) {
    case '&':
    case '|':
        mode = token;
        token = GetNextToken(expr, pos);
        if (token != '(')
            throw std::runtime_error("Expected (");
        token = GetNextToken(expr, pos);
        dns = ParseExpr(expr, pos, token);
        if (token != ')')
            throw runtime_error("Expected )");
        if ((token = GetNextToken(expr, pos)) != '(')
            throw runtime_error("Expected (");
        token = GetNextToken(expr, pos);
        deb(mode);
        dns = (mode == '&') ? AndExprs(dns, ParseExpr(expr, pos, token))
                            : OrExprs(dns, ParseExpr(expr, pos, token));
        if (token != ')')
            throw runtime_error("Expected )");
        token = GetNextToken(expr, pos);
        break;
    case '(':
        token = GetNextToken(expr, pos);
        if (token == '(') {
            token = GetNextToken(expr, pos);
        }
        dns = ParseExpr(expr, pos, token);
        token = GetNextToken(expr, pos);
        if (token != ')')
            throw runtime_error("Expected )");
        break;
    case ')':
        throw runtime_error("Unexpected )");
    default:
        return ParseBaseExpr(expr, pos, token);
    }

    return dns;
}

vector<int> Solution::ParseBaseExpr(const string &expr, size_t &pos,
                                    char &token) {
    int first_num = token - '0', second_num = 0;
    while (isdigit(token = GetNextToken(expr, pos))) {
        first_num = first_num * 10 + (token - '0');
    }

    char oper = token;
    if (oper != ':' && token != '~')
        throw runtime_error("Expected : or ~");

    token = GetNextToken(expr, pos);
    second_num = token - '0';
    while (isdigit(token = GetNextToken(expr, pos))) {
        second_num = second_num * 10 + (token - '0');
    }

    deb(first_num, oper, second_num);

    // Fetch DNs meeting attr key and value requirements
    if (oper == ':') {
        return PositiveFetchDns(first_num, second_num);
    } else if (oper == '~') {
        return NegativeFetchDns(first_num, second_num);
    }
    throw runtime_error("Illegal operater " + to_string(oper));
}

int main(int argc, char *argv[]) {
    Solution s;
    cin >> s.n;
    // Read users
    for (int i = 0; i < s.n; i++) {
        int dn, num_attrs;
        cin >> dn >> num_attrs;
        auto u = make_shared<User>(dn, num_attrs);
        int attr_key, attr_val;
        for (int j = 0; j < num_attrs; j++) {
            cin >> attr_key >> attr_val;
            u->attrs_.insert({attr_key, attr_val});
            s.AddAttrKeyToDNMap(attr_key, dn);
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
        size_t pos = 1;
        char token = expr.at(0);
        s.corresponding_dns_ = s.ParseExpr(expr, pos, token);
        cout << s.CorrespondingDn();
    }

    return 0;
}
