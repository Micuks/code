#include "parser.h"

namespace std {
namespace parser {
SymbolList Lex::process() {
    SymbolList sl;
    // end of analysis process sign
    bool end = false;
    // alias to fs
    ifstream &f = this->fs;
    try {
        f.read(buffer, BUFFER_SIZE - 1);
    } catch (ifstream::failure &e) {
        cout << "Read to buffer failure.\n";
    }
    if (f.gcount() < BUFFER_SIZE - 1) {
        buffer[f.gcount()] = EOF;
    }
    buffer[BUFFER_SIZE - 1] = EOF;

    // initial state
    int state = 0;
    while (!end) {
        get_char();
        if (ch != EOF) {
            numChar++;
        }
        if (ch == EOF && pForward == BUFFER_SIZE - 1) {
            f.read(buffer, BUFFER_SIZE - 1);
            if (f.gcount() < BUFFER_SIZE - 1) {
                buffer[f.gcount()] = EOF;
            }
            continue;
        }
        // EOF in source file, should not be transparent to Lex
        if (ch == EOF && pForward != BUFFER_SIZE - 1) {
            end = true;
        }
        // separate line with ; instead if \n
        // when not in char or string state
        if (ch == ';') {
            if (state != 21 && state != 22) {
                numLines++;
            }
        }

        switch (state) {
        case 0:
            if (is_letter()) {
                // letter state
                state = 1;
                cat();
            } else if (is_digit()) {
                if (ch != '0') {
                    // integer state
                    state = 2;
                    cat();
                } else if (ch == '0') {
                    // TODO: implement hex, bin and octtal decimal mode.
                    // state =
                    // cat();
                }
            } else {
                switch (ch) {
                case '<':
                    state = 8;
                    break;
                case '>':
                    state = 9;
                    break;
                case '=':
                    state = 10;
                    break;
                case '!':
                    state = 11;
                    break;
                case '&':
                    state = 12;
                    break;
                case '|':
                    state = 13;
                    break;
                case '~':
                    state = 14;
                    break;
                case '+':
                    state = 15;
                    break;
                case '-':
                    state = 16;
                    break;
                case '*':
                    state = 17;
                    break;
                case '/':
                    state = 18;
                    break;
                case '%':
                    state = 19;
                    break;
                case '^':
                    state = 20;
                    break;
                case '(':
                    addSymbol("(");
                    // TODO case '?'
                    break;
                case ')':
                    addSymbol(")");
                    break;
                case '{':
                    addSymbol("{");
                    break;
                case '}':
                    addSymbol("}");
                    break;
                case '[':
                    addSymbol("[");
                    break;
                case ']':
                    addSymbol("]");
                    break;
                case '\'':
                    state = 21;
                    break;
                case '"':
                    state = 22;
                    break;
                case ' ':
                case '\n':
                case EOF:
                    break;
                default:
                    string err = "Illegal char " + to_string(ch);
                    logError(err);
                    break;
                }
            }
        case 1: // Identifer state
            if (is_letter() || is_digit()) {
                cat();
                state = 1;
            } else {
                state = 0;
                if (is_keyword()) {
                    addSymbol("keyword", bufStr);
                } else {
                    addSymbol("id", bufStr);
                }
                // Unget last char from buffer.
                unget_char();
                // Clear symbol cache bufStr.
                clrStr();
            }
            break;
        case 2: // Integer state
            if (is_digit()) {
                cat();
                state = 2;
            } else if (ch == '.') {
                cat();
                state = 3;
            } else if (ch == 'E' || ch == 'e') {
                cat();
                state = 5;
            } else {
                state = 0;
                addSymbol("integer", bufStr);
                unget_char();
                clrStr();
            }
        case 3: // '.' state
            if (is_digit()) {
                cat();
                state = 4;
            } else {
                state = 0;
                // concat 0 to bufStr
                bufStr.push_back('0');
                addSymbol("float", bufStr);
                unget_char();
                clrStr();
            }
            break;
        case 4: // after '.' state
            if (is_digit()) {
                cat();
                state = 4;
            } else if (ch == 'E' || ch == 'e') {
                // exp state
                cat();
                state = 5;
            } else {
                state = 0;
                addSymbol("float", bufStr);
                unget_char();
                clrStr();
            }
        case 5:
            if (is_digit()) {
                cat();
                state = 7;
            } else if (ch == '+' || ch == '-') {
                cat();
                state = 6;
            } else {
                state = 0;
                logError("Expected exponent");
                unget_char();
                clrStr();
            }
        case 6:
            if (is_digit()) {
                cat();
                state = 7;
            } else {
                state = 0;
                logError("Expected exponent");
                unget_char();
                clrStr();
            }
        case 7:
            if (is_digit()) {
                cat();
                state = 7;
            } else {
                state = 0;
                addSymbol("float", bufStr);
                unget_char();
                clrStr();
            }
        case 8:
            if (ch == '=') {
                addSymbol("relop", "<=");
                state = 0;
            } else if (ch == '<') {
                addSymbol("bitop", "<<");
                state = 0;
            } else {
                addSymbol("relop", "<");
                state = 0;
                unget_char();
            }
        case 9:
            if(ch == '=') {
              addSymbol("relop", ">=");
              state = 0;
            } else if(ch == '>') {
            }
        }
    }
}

int main(int argc, char **argv) {
    ifstream fs;
    Lex lex(FNAME);
    lex.process();
    lex.print();
}
} // namespace parser
} // namespace std