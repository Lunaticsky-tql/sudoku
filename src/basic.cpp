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
vector<Board> generateGame(vector<Board>&& boards,int minHole,int maxHole,bool isUnique)
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(minHole,maxHole);
    int holeNum;
    for(auto& board:boards)
    {
        holeNum = dis(gen);
        while(--holeNum){
            int x = rd0to8();
            int y = rd0to8();
            while(board[x][y]==0)
            {
                x = rd0to8();
                y = rd0to8();
            }
            board[x][y] = 0;
        }
    }
    return boards;
}