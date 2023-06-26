//
// Created by LENOVO on 2023/6/26.
//

#ifndef SUDOKU_COLOR_PRINT_H
#define SUDOKU_COLOR_PRINT_H
#ifdef _WIN32

#include <iostream>
#endif
enum ConsoleColor {
    ERR = 4,
    WARNING = 6,
    INFO = 7,
};
#endif //SUDOKU_COLOR_PRINT_H

void color_print(const char *s, int color) {
    switch (color) {
        case ERR:
            std::cerr << "\033[31m" << s << "\033[0m";
            break;
        case WARNING:
            std::cout << "\033[33m" << s << "\033[0m";
            break;
        case INFO:
            std::cout << "\033[37m" << s << "\033[0m";
            break;
        default:
            std::cout << s;
    }
}

void color_print(const std::string &s, int color) {
    //print colored text on terminal compatible with windows and linux
    color_print(s.c_str(), color);
}

void print_error(const char *s) {
    color_print("[ERROR] ", ERR);
    color_print(s, ERR);
    std::cerr << std::endl;
}
