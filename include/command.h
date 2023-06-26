#ifndef COMMAND
#define COMMAND

#include<string>
#include"exception.h"
#include "color_print.h"

#endif
class Command{
public:

};
Command parseCommand(int argc, char *argv[]) {
    Command command = Command();
    try {
        if (argc <= 1) {
            throw ParseArgException("No argument provided\nUsage: sudoku.exe <command> [options]");
        }
    }
    catch (std::exception& e) {
        print_error(e.what());

        exit(0);
    }
    return command;
}