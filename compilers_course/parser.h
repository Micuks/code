#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

const int BUFFER_SIZE = 1024;
const std::string FNAME = "sin";

namespace std {
namespace parser {

unordered_set<string> keywords = {
    "auto",   "switch",   "case",     "for",    "do",     "while",
    "int",    "char",     "float",    "double", "if",     "else",
    "return", "break",    "continue", "const",  "enum",   "extern",
    "goto",   "register", "restrict", "short",  "signed", "unsigned",
    "sizeof", "static",   "inline",   "struct", "class",  "typedef",
    "union",  "void",     "volatile"};

class Symbol {
  public:
    Symbol(string _notation, string _property)
        : notation(_notation), property(_property) {}
    string getNotation() { return notation; }
    string getProperty() { return property; }
    void incCount() { count++; }
    int getCount() { return count; }
    string toString() { return "<" + notation + ", " + property + ">"; }

  private:
    // symbol' notation
    string notation;
    // symbol's property
    string property;
    // count of symbol appearance time
    int count;
};

class SymbolList {
  public:
    SymbolList();
    bool add(Symbol symbol);
    bool
    add(const string &notation,
        const string &property); // TODO: when symbol already exists, count+1;
                                 // else create new symbol in SymbolList.
    bool del(const Symbol &symbol);
    bool del(const string &pattern);
    Symbol find(const string &pattern);
    void toString();
    void print();

  private:
    vector<Symbol> sl;
    int numSymbol;
};

class Lex {
  public:
    Lex(const string &filename) : numLines(0), numChar(0), pForward(-1) {
        try {
            fs.open(FNAME);
        } catch (ifstream::failure &e) {
            cout << "Exception opening file.\n";
        }
        numLines = 0;
    };

    ~Lex() {
        try {
            fs.close();
        } catch (ifstream::failure &e) {
            cout << "Exception closing file.\n";
        }
    }
    SymbolList process();
    void print();

  private:
    ifstream fs;
    SymbolList sl;
    char buffer[BUFFER_SIZE];
    int numLines;
    int numChar;
    char ch;       // store next char
    string bufStr; // store current string
    int pForward;  // forward pointer of buffer
    int pBackward;

    void get_char() {
        pForward = (pForward + 1) % BUFFER_SIZE;
        ch = buffer[pForward];
    }
    bool is_letter() { return (isalpha(ch) || ch == '_'); }
    bool is_digit() { return (ch >= '0' && ch <= '9'); }
    bool is_keyword() { return (keywords.find(bufStr) != keywords.end()); }
    void cat() { bufStr.push_back(ch); } // concat ch to the end of bufStr.
    void clrStr() { bufStr.clear(); }
    void unget_char() {
        pForward = (pForward - 1) % BUFFER_SIZE;
        // decrease char counter when
        // ch is not EOF
        if (ch != EOF) {
            numChar--;
        }
        // decrease line counter when
        // ch is end of line symbol ';'
        if (ch == ';') {
            numLines--;
        }
    }

    void addSymbol(const string &notation, const string &property = "") {
        sl.add(notation, property);
    }

    // log zone
    void logError(const string &err) {
        string msg = "ERROR: " + err + "in L" + to_string(numLines);
        cout << msg << endl;
    }
};
} // namespace parser
} // namespace std
#endif