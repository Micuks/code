#ifndef CLI_PARSER_H
#define CLI_PARSER_H
#include <exception>
#include <string>
#include <unordered_map>

/**
 * A simple tool to parse command line args passed to the program.
 */
class CLIParser {
  private:
    int argc;
    char **argv;
    void hashArgs();
    std::string helpStr();

  public:
    std::unordered_map<std::string, std::string> args;

    CLIParser(int argc, char **argv) : argc(argc), argv(argv) {}
    void argParse();
};
#endif
