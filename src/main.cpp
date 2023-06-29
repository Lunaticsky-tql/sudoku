#include <iostream>
#include<cstring>
#include <string>
#include "command.h"
#include "gtest/gtest.h"



int main(int argc, const char* argv[]) {
    Command command = parseArgs(argc, argv);
    command.showCommand();
    distributeTask(command);
}


