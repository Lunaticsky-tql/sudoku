#pragma warning(disable:4996);
#ifndef COMMAND
#define COMMAND

#include<string>
#include <utility>
#include <fstream>
#include "exception.h"
#include "color_print.h"
#include "basic.h"

#endif
enum GameType {
    GENERATE_SOLUTION_MAP,
    SOLVE_SUDOKU,
    GENERATE_SUDOKU
};
enum GameDifficulty {
    EASY = 1,
    MEDIUM,
    HARD
};

int parseNumber(const std::string &s) {
    int number = 0;
    for (char i: s) {
        if (i < '0' || i > '9') {
            throw ParseArgException("Invalid number provided\nUsage: sudoku.exe -c <number>");
        }
        number = number * 10 + (i - '0');
    }
    return number;
}

std::pair<int, int> parseRange(const std::string &s) {
    int start = 0;
    int end = 0;
    bool isStart = true;
    for (char i: s) {
        if (i == '~') {
            isStart = false;
            continue;
        }
        if (i < '0' || i > '9') {
            throw ParseArgException("Invalid range provided\nUsage: sudoku.exe -n <number> -r xx~xx");
        }
        if (isStart) {
            start = start * 10 + (i - '0');
        } else {
            end = end * 10 + (i - '0');
        }
    }
    return {start, end};
}

class Command {
public:
    int gameNumber{};
    int gameType;
    int gameDifficulty = EASY;
    std::string filePath;
    bool isUnique = false;
    std::pair<int, int> holeRange;

    Command(int gameType, int gameNumber, bool isUnique = false) {
        this->gameType = gameType;
        this->gameNumber = gameNumber;
        this->isUnique = isUnique;
    }

    Command(int gameType, std::string filePath) {
        this->gameType = gameType;
        this->filePath = std::move(filePath);
    }

    Command(int gameType, int gameNumber, int gameDifficulty) {
        this->gameType = gameType;
        this->gameNumber = gameNumber;
        this->gameDifficulty = gameDifficulty;
    }

    Command(int gameType, int gameNumber, std::pair<int, int> holeRange) {
        this->gameType = gameType;
        this->gameNumber = gameNumber;
        this->holeRange = holeRange;
    }

    void showCommand() const {
        switch (gameType) {
            case GENERATE_SOLUTION_MAP:
                std::cout << "Command: generate solution map" << std::endl;
                std::cout << "Number: " << gameNumber << std::endl;
                break;
            case SOLVE_SUDOKU:
                std::cout << "Command: solve sudoku" << std::endl;
                std::cout << "File path: " << filePath << std::endl;
                break;
            case GENERATE_SUDOKU:
                std::cout << "Command: generate sudoku" << std::endl;
                std::cout << "Number: " << gameNumber << std::endl;
                if (isUnique) {
                    std::cout << "Unique: true" << std::endl;
                } else if (gameDifficulty == EASY) {
                    std::cout << "Difficulty: easy" << std::endl;
                } else if (gameDifficulty == MEDIUM) {
                    std::cout << "Difficulty: medium" << std::endl;
                } else if (gameDifficulty == HARD) {
                    std::cout << "Difficulty: hard" << std::endl;
                } else {
                    std::cout << "Hole range: " << holeRange.first << "~" << holeRange.second << std::endl;
                }
                break;
        }
    }

};

Command parseArgs(int argc, const char *argv[]) {
    try {
        if (argc <= 1) {
            throw ParseArgException("No argument provided!\nUsage: sudoku.exe <command> [options]");
        }
        std::string firstArg = argv[1];
        if (firstArg == "-c") {
            if (argc <= 2) {
                throw ParseArgException("No number provided!\nUsage: sudoku.exe -c <number>");
            }
            std::string secondArg = argv[2];
            int num = parseNumber(secondArg);
            if (num < 1 || num > 1000000) {
                throw ParseArgException("Solution number should be between 1 and 1000000!");
            }
            return {GENERATE_SOLUTION_MAP, num};
        } else if (firstArg == "-s") {
            if (argc <= 2) {
                throw ParseArgException("No file path provided\nUsage: sudoku.exe -s <file path>");
            }
            std::string filePath = argv[2];
            // check if the file path is existed
            std::ifstream file(filePath);
            if (!file) {
                throw ParseArgException("File not found!");
            }
            return {SOLVE_SUDOKU, filePath};
        } else if (firstArg == "-n") {
            if (argc <= 2) {
                throw ParseArgException("No number provided\nUsage: sudoku.exe -n <number>");
            }
            std::string secondArg = argv[2];
            int num = parseNumber(secondArg);
            if (num < 1 || num > 10000) {
                throw ParseArgException("Sudoku number should be between 1 and 1000000!");
            }
            if (argc -= 3, argc) {
                std::string thirdArg = argv[3];
                if (thirdArg == "-u") {
                    return {GENERATE_SUDOKU, num, true};
                } else if (thirdArg == "-m") {
                    if (--argc) {
                        std::string fourthArg = argv[4];
                        int difficulty = parseNumber(fourthArg);
                        if (difficulty < EASY || difficulty > HARD) {
                            throw ParseArgException("Difficulty should be between 1 and 3!");
                        }
                        return {GENERATE_SUDOKU, num, difficulty};
                    }
                    throw ParseArgException("No difficulty provided\nUsage: sudoku.exe -n <number> -m <difficulty>");
                } else if (thirdArg == "-r") {
                    // hole number ,eg: "20~55"
                    if (--argc) {
                        std::string fourthArg = argv[4];
                        return {GENERATE_SUDOKU, num, parseRange(fourthArg)};
                    }
                    throw ParseArgException("No range provided\nUsage: sudoku.exe -n <number> -r xx~xx");
                }
            }
            return { GENERATE_SUDOKU, num };
        } else {
            throw ParseArgException("Invalid command provided\nUsage: sudoku.exe <command> [options]");
        }
    }
    catch (std::exception &e) {
        print_error(e.what());
        throw ParseArgException("Parse argument failed!");
    }
    return {0, 0};
}

void distributeTask(const Command &command) {
    switch (command.gameType) {
        case GENERATE_SOLUTION_MAP:
            if(mapGenerate(command.gameNumber)){
                std::cout << "Solution map generated successfully!" << std::endl;
            }
            break;
        default:
            break;

    }

}