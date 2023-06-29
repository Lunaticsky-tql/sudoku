//
// Created by LENOVO on 2023/6/26.
//

#ifndef SUDOKU_EXCEPTION_H
#define SUDOKU_EXCEPTION_H

#include<exception>
// some definitions for Exception class to use
class Exception : public std::exception {
protected:
    const char *msg;
public:
    Exception() noexcept {
        this->msg = "Unknown Exception";
    }

    explicit Exception(const char *msg) noexcept {
        this->msg = msg;
    }

    ~Exception() override = default;

    [[nodiscard]] const char *what() const noexcept override {
        return msg;
    }
};

class ParseArgException : public Exception {
public:
    ParseArgException() noexcept {
        this->msg = "Unknown ParseArgException";
    }

    explicit ParseArgException(const char *msg) noexcept {
        this->msg = msg;
    }

    ~ParseArgException() override = default;

    [[nodiscard]] const char *what() const noexcept override {
        return msg;
    }
};

#endif //SUDOKU_EXCEPTION_H
