#include"basic.h"

vector<Board> mapGenerate(int n) {
    vector<Board> boards;
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
        next_permutation(basic_line + 1, basic_line + 9);
    }
    return boards;
}

bool writeBoards2File(const vector<Board> &boards, const std::string& path) {
    try {
        std::ofstream fp(path);
        if (!fp.is_open()) {
            throw std::ifstream::failure("open file failed");
        }
        fp << boards.size() << '\n';
        for (auto &board: boards) {
            board.printBoard(fp);
        }
        return true;
    }
    catch (std::ifstream::failure &e) {
        print_error(e.what());
        return false;
    }
}

bool generateQuesN(int n) {
    char inter_result[200];
    inter_qb[9][1] = '\0';
    inter_qb[9][0] = '\n';

    auto *ques_boards = new Board[n];
    int board_id = 0;

    FILE *fpMap;
    FILE *fpQuestion;

    fpQuestion = fopen(QUESTION_PATH, "w");
    fpMap = fopen(SOLUTION_MAP_PATH, "r");

    while (n--) {
        inter_result[0] = '\0';
        for (int i = 0; i < 9; i++) {
            fgets(inter_qb[i], 20, fpMap);
        }
        fgetc(fpMap);
        int und[9] = {0, 6, 12, 54, 60, 66, 108, 114, 120};
        int add[9] = {0, 2, 4, 18, 20, 22, 36, 38, 40};

        for (int k: und) {
            int i, j, temp[2];
            temp[0] = rand() % 9;
            temp[1] = rand() % 9;
            while (temp[0] == temp[1]) {
                temp[1] = rand() % 9;
            }
            for (int u: temp) {
                int g;
                g = k + add[u];
                i = g / 18;
                j = g % 18;
                inter_qb[i][j] = '0';
            }
        }

        int par;
        par = 2 + rand() % 19;
        while (par--) {
            int k = rand() % 81;
            int i = k / 9;
            int j = k % 9;
            j *= 2;
            if (inter_qb[i][j] != '0')
                inter_qb[i][j] = '0';
            else
                par++;
        }

        for (int i = 0; i < 10; i++) {
            strncat(inter_result, inter_qb[i], 20);
            if (i < 9) {
                for (int m = 0; m < 9; m++) {
                    ques_boards[board_id][i][m] = inter_qb[i][2 * m] - '0';
                }
            }
        }
        if (!n) {
            inter_result[161] = '\0';
        }
        //cout << "id:" << board_id << endl;
        //ques_boards[board_id].printBoard();
        board_id++;
        fputs(inter_result, fpQuestion);
    }
    fclose(fpQuestion);
    fclose(fpMap);

    return true;
}

bool generateQuesM(int n, int level) {
    Board *ques_boards = new Board[n];
    int board_id = 0;
    char inter_result[200];
    inter_qb[9][0] = '\n';
    inter_qb[9][1] = '\0';

    FILE *fpQuestion;
    FILE *fpMap;
    fpMap = fopen(SOLUTION_MAP_PATH, "r");
    fpQuestion = fopen(QUESTION_PATH, "w");

    while (n--) {
        inter_result[0] = '\0';
        for (int i = 0; i < 9; i++) {
            fgets(inter_qb[i], 20, fpMap);
        }
        fgetc(fpMap);
        int und[9] = {0, 6, 12, 54, 60, 66, 108, 114, 120};
        int add[9] = {0, 2, 4, 18, 20, 22, 36, 38, 40};

        for (int k: und) {
            int i, j, temp[2];
            temp[0] = rand() % 9;
            temp[1] = rand() % 9;
            while (temp[0] == temp[1]) {
                temp[1] = rand() % 9;
            }
            for (int t: temp) {
                int g;
                g = k + add[t];
                j = g % 18;
                i = g / 18;
                inter_qb[i][j] = '0';
            }
        }

        int par = 0;  // 2-42
        // 2-20
        if (level == 1) {
            par = 2 + rand() % 19;
        }
        // 21-31 
        if (level == 2)
            par = 21 + rand() % 11;
        // 32-42 
        if (level == 3)
            par = 32 + rand() % 11;
        while (par--) {
            int k = rand() % 81;
            int i = k / 9;
            int j = k % 9;
            j *= 2;
            if (inter_qb[i][j] != '0')
                inter_qb[i][j] = '0';
            else
                par++;
        }

        for (int i = 0; i < 10; i++) {
            strncat(inter_result, inter_qb[i], 20);
            if (i < 9) {
                for (int m = 0; m < 9; m++) {
                    ques_boards[board_id][i][m] = inter_qb[i][2 * m] - '0';
                }
            }
        }
        if (!n) {
            inter_result[161] = '\0';
        }
        board_id++;
        fputs(inter_result, fpQuestion);
    }
    fclose(fpMap);
    fclose(fpQuestion);

    return true;
}