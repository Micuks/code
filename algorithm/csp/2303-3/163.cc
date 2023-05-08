#include "debug.hh"
#include <cctype>
#include <cstddef>
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class User {
  public:
    User();
    User(User &&) = default;
    User(const User &) = default;
    User(int dn) : dn_(dn) {}
    User &operator=(User &&) = default;
    User &operator=(const User &) = default;
    ~User();

    int dn_;
    int num_attrs_;
    unordered_map<int, int> attrs_;
};

class Expr {
  public:
    Expr() = default;
    Expr(Expr &&) = default;
    Expr(const Expr &) = default;
    Expr &operator=(Expr &&) = default;
    Expr &operator=(const Expr &) = default;
    ~Expr() = default;
};

class Solution {
  public:
    Solution() = default;
    Solution(Solution &&) = default;
    Solution(const Solution &) = default;
    Solution &operator=(Solution &&) = default;
    Solution &operator=(const Solution &) = default;
    ~Solution() = default;
    void AddUser(shared_ptr<User> u) { dn_to_users_[u->dn_] = u; }
    void AddAttrKeyToDNMap(int attr_key, int dn) {
        attr_key_to_users[attr_key].push_back(dn);
    }
    char GetNextToken(const string &s, size_t &pos);
    void ParseExpr(const string &expr, size_t &pos, char &token);
    void ParseBaseExpr(const string &expr, size_t &pos, char &token);
    void InitCorrespondingDns() { corresponding_dns_.clear(); }
    const string CorrespondingDn() {
        stringstream ss;
        for (auto &dn : corresponding_dns_) {
            ss << dn << ' ';
        }
        ss << endl;
        return ss.str();
    }
    void PositiveFetchDns(int key, int value);
    void NegativeFetchDns(int key, int value);

    int n, m;
    unordered_map<int, vector<int>> attr_key_to_users;
    unordered_map<int, shared_ptr<User>> dn_to_users_;

    // temporary
    vector<int> corresponding_dns_;
};

void Solution::PositiveFetchDns(int key, int value) {
    InitCorrespondingDns();
    auto users = attr_key_to_users[key];
    for (auto &dn : users) {
        auto user = dn_to_users_[dn];
        if (!user)
            throw runtime_error("Expected user " + to_string(dn));
        auto user_val = user->attrs_[key];
        if (!user_val)
            throw runtime_error("Expected value of user " + to_string(dn) +
                                "'s attribute " + to_string(key));
        if (user_val == value)
            corresponding_dns_.push_back(dn);
    }
}

void Solution::NegativeFetchDns(int key, int value) {
    InitCorrespondingDns();
    auto users = attr_key_to_users[key];
    for (auto &dn : users) {
        auto user = dn_to_users_[dn];
        if (!user)
            throw runtime_error("Expected user" + to_string(dn));
        auto user_val = user->attrs_[key];
        if (!user_val)
            throw runtime_error("Expected value of user " + to_string(dn) +
                                "'s attribute " + to_string(key));
        if (user_val != value)
            corresponding_dns_.push_back(dn);
    }
}

char Solution::GetNextToken(const string &s, size_t &pos) {
    while (pos < s.size() && isspace(s[pos]))
        ++pos;
    return pos < s.size() ? s[pos++] : '\0';
}

void Solution::ParseExpr(const string &expr, size_t &pos, char &token) {
    switch (token) {
    case '&':
    case '|':
        token = GetNextToken(expr, pos);
        if (token != '(')
            throw std::runtime_error("Expected (");
        token = GetNextToken(expr, pos);
        ParseExpr(expr, pos, token);
        if (token != ')')
            throw runtime_error("Expected )");
        if ((token = GetNextToken(expr, pos) != '('))
            throw runtime_error("Expected (");
        token = GetNextToken(expr, pos);
        ParseExpr(expr, pos, token);
        if ((token = GetNextToken(expr, pos)) != ')')
            throw runtime_error("Expected )");
        token = GetNextToken(expr, pos);
        break;
    case '(':
        token = GetNextToken(expr, pos);
        if (token == '(') {
            token = GetNextToken(expr, pos);
        }
        ParseExpr(expr, pos, token);
        token = GetNextToken(expr, pos);
        if (token != ')')
            throw runtime_error("Expected )");
        break;
    case ')':
        throw runtime_error("Unexpected )");
        break;
    default:
        ParseBaseExpr(expr, pos, token);
        break;
    }
}

void Solution::ParseBaseExpr(const string &expr, size_t &pos, char &token) {
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

    // Fetch DNs meeting attr key and value requirements
    if (oper == ':') {
        PositiveFetchDns(first_num, second_num);
    } else if (oper == '~') {
        NegativeFetchDns(first_num, second_num);
    }
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
            u->attrs_[attr_key] = attr_val;
            s.AddAttrKeyToDNMap(attr_key, dn);
        }
        s.AddUser(u);
    }

    // Read exprs
    cin >> s.m;
    for (int i = 0; i < s.m; i++) {
        // Initialization
        s.InitCorrespondingDns();

        string expr;
        getline(cin, expr);
        size_t pos = 0;
        char token = expr[0];
        s.ParseExpr(expr, pos, token);
        cout << s.CorrespondingDn();
    }

    return 0;
}
