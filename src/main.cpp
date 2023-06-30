#include "command.h"


int main(int argc, const char* argv[]) {
    Command command = parseArgs(argc, argv);
    command.showCommand();
    distributeTask(command);
}
