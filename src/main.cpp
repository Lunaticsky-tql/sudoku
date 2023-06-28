#include <iostream>
#include<cstring>
#include <string>
#include "command.h"
#if defined TEST
#include "test.h"
#endif

int main(int argc, const char *argv[]) {
    Command command = parseArgs(argc, argv);
    command.showCommand();
}

