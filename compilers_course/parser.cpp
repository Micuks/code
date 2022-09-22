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
                    cout << "ERROR: Illegal char" << ch << "in L:" << numLines
                         << endl;
                    break;
                }
            }
        case 1:
            if (is_letter() || is_digit()) {
                cat();
                state = 1;
            } else {
                unget_char();
                state = 0;
                if (is_keyword()) {
                    addSymbol("keyword", str);
                } else {
                    addSymbol("id", str);
                }
            }
            break;
        case 2:
            
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