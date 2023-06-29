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
    SUCCESS=10
};
inline void color_print(const char *s, int color) {
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
        case SUCCESS:
            std::cout << "\033[32m" << s << "\033[0m";
            break;
        default:
            std::cout << s;
    }
}

inline void print_error(const char *s) {
    color_print("[ERROR] ", ERR);
    color_print(s, ERR);
    std::cerr << std::endl;
}
inline void print_success(const char *s) {
    color_print(s, SUCCESS);
    std::cout << std::endl;
}
#endif //SUDOKU_COLOR_PRINT_H