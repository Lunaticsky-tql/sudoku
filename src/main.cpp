#include <iostream>
#include<cstring>
#include <string>
#include "command.h"



Command parseCommand(int argc, char *argv[]);

int main(int argc, char *argv[]) {
    std::cout<<"hello world"<<std::endl;
    Command command = parseCommand(argc, argv);
}

