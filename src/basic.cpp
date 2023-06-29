#include"basic.h"

std::vector<Board> mapGenerate(int n) {
    std::vector<Board> boards;
    int basic_line[9] = {5, 1, 2, 3, 4, 6, 7, 8, 9};
    int shift[9] = {0, 3, 6, 1, 4, 7, 2, 5, 8};
    Board board;
    while (n--) {
        for (int i = 0; i < 9; i++) {
            board[0][i] = basic_line[i];
        }
        for (int i = 1; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                board[i][j] = board[0][(j + shift[i]) % 9];
            }
        }
        board.shuffleBoard();
        boards.emplace_back(board);
        std::next_permutation(basic_line + 1, basic_line + 9);
    }
    return boards;
}

bool writeBoards2File(const std::vector<Board> &boards, const std::string &path) {
    try {
        std::ofstream fp(path);
        if (!fp.is_open()) {
            throw std::ifstream::failure("open file failed");
        }
        fp << boards.size() << '\n';
        for (auto &board: boards) {
            board.writeBoard(fp);
        }
        return true;
    }
    catch (std::ifstream::failure &e) {
        print_error(e.what());
        return false;
    }
}

std::vector<Board> readBoardsFromFile(const std::string &filePath) {
    std::vector<Board> boards;
    try {
        std::ifstream fp(filePath);
        if (!fp.is_open()) {
            throw std::ifstream::failure("open file failed");
        }
        int size;
        fp >> size;
        for (int i = 0; i < size; i++) {
            Board board;
            board.readBoard(fp);
            boards.emplace_back(board);
        }
        return boards;
    }
    catch (std::ifstream::failure &e) {
        print_error(e.what());
        return boards;
    }
}

std::vector<Board> generateGame(std::vector<Board> &&boards, int minHole, int maxHole, bool isUnique) {
    std::random_device m_rd;
    std::mt19937 m_gen(m_rd());
    std::uniform_int_distribution<> dis(minHole, maxHole);
    std::vector<Board> result;
    int holeNum;
    if(isUnique) {
        for (auto &board: boards) {
            holeNum = dis(m_gen);

            Board tmp = board;
            while (true) {
                board = tmp;
                while (holeNum--) {
                    int x = rd0to8();
                    int y = rd0to8();
                    while (board[x][y] == 0) {
                        x = rd0to8();
                        y = rd0to8();
                    }
                    board[x][y] = 0;
                }
                SudoSolver solver;
                std::vector<Board> solution = solver.solve(board);
                if (solution.size() == 1) {
                    result.emplace_back(board);
                    break;
                }
            }
        }
        return result;
    }
    for (auto &board: boards) {
        holeNum = dis(m_gen);
        std::cout<<holeNum<<std::endl;
        while (holeNum--) {
            int x = rd0to8();
            int y = rd0to8();
            while (board[x][y] == 0) {
                x = rd0to8();
                y = rd0to8();
            }
            board[x][y] = 0;
        }
    }
    return boards;
}

std::vector<std::vector<Board>> solveSudoku(std::vector<Board> &&boards) {
    std::vector<std::vector<Board>> solutions;
    SudoSolver solver;

    for (int i = 0; i < boards.size(); i++) {
        std::vector<Board> solution = solver.solve(boards[i]);
        solutions.emplace_back(solution);
        std::string message = "Solving board " + std::to_string(i + 1) + " of " + std::to_string(boards.size());
        print_info(message.c_str());
    }
    for (std::vector<Board> &solution: solutions) {
            for(auto &board: solution){
                board.printBoard();
            }
    }
    return solutions;
}

bool writeAnswers2File(std::vector<std::vector<Board>> &&solutions) {
    try {
        std::ofstream fp(SOLUTION_MAP_PATH);
        if (!fp.is_open()) {
            throw std::ifstream::failure("open file failed");
        }
        fp << solutions.size() << '\n';
        for (auto &solution: solutions) {
            fp << solution.size() << '\n';
            for (auto &board: solution) {
                board.writeBoard(fp);
            }
        }
        return true;
    }
    catch (std::ifstream::failure &e) {
        print_error(e.what());
        return false;
    }

}