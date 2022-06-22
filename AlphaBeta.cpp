#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <array>
#include <set>
#include <limits>
#include <unordered_map>
#include <queue>

enum SPOT_STATE {
    EMPTY = 0,
    BLACK = 1,
    WHITE = 2
};

const int SIZE = 15;
const int INF = std::numeric_limits<int>::max()/4; //To prevent overflow
const int MAXDEPTH = 8;


using Board = std::array<std::array<int, SIZE>, SIZE>;
using Coordinate = std::pair<int, int>;

int player;
Board board;

namespace BoardAnal {

int getScore(int length, int closed, bool isMyTurn) {
    if(length >= 5) return 2*INF;
    if(closed == 2) return 0;

    switch(length) {
    case 4: if (isMyTurn) return INF;
            return (closed == 0)? 250000: 200;
    case 3: if(closed == 0) return (isMyTurn)? 50000: 200;
            else return (isMyTurn)? 10: 5;
    case 2: if (closed == 0) return (isMyTurn)? 7: 5;
            else return 3;
    case 1: return 1;
    case 0: return 0;
    }
return 0;
}

int Horizontal(const Board &bd, const int player, const int playertomove) {
    int score = 0, len = 0, closed = 2;
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if(bd[i][j] == player) len++;
            else if (bd[i][j] == 0) {
                score += getScore(len, closed - 1, player == playertomove);
                len = 0, closed = 1;
            } else {
                score += getScore(len, closed, player == playertomove);
                len = 0, closed = 2;
            }
        }
        score += getScore(len, closed, player == playertomove);
        len = 0, closed = 2;
    }
    return score;
}

int Vertical(const Board &bd, const int player, const int playertomove) {
    int score = 0, len = 0, closed = 2;
    for(int j = 0; j < SIZE; j++) {
        for(int i = 0; i < SIZE; i++) {
            if(bd[i][j] == player) len++;
            else if (bd[i][j] == 0) {
                score += getScore(len, closed - 1, player == playertomove);
                len = 0, closed = 1;
            } else {
                score += getScore(len, closed, player == playertomove);
                len = 0, closed = 2;
            }
        }
        score += getScore(len, closed, player == playertomove);
        len = 0, closed = 2;
    }
    return score;
}

int Sinistral(const Board &bd, const int player, const int playertomove) {
    int score = 0, len = 0, closed = 2;
    for(int d = 1-SIZE; d < SIZE; d++) {
        for(int i = (d < 0)? 0: d; i < SIZE && i-d < SIZE; i++) {
            if(bd[i][i-d] == player) len++;
            else if (bd[i][i-d] == 0) {
                score += getScore(len, closed - 1, player == playertomove);
                len = 0, closed = 1;
            } else {
                score += getScore(len, closed, player == playertomove);
                len = 0, closed = 2;
            }
        }
        score += getScore(len, closed, player == playertomove);
        len = 0, closed = 2;
    }
    return score;
}

int Dextral(const Board &bd, const int player, const int playertomove) {
    int score = 0, len = 0, closed = 2;
    for(int N = 0; N < 2 * SIZE - 1; N++) {
        for(int i = (N < SIZE)? 0: N-SIZE+1; i < SIZE && N-i < SIZE; i++) {
            if(bd[i][N-i] == player) len++;
            else if (bd[i][N-i] == 0) {
                score += getScore(len, closed - 1, player == playertomove);
                len = 0, closed = 1;
            } else {
                score += getScore(len, closed, player == playertomove);
                len = 0, closed = 2;
            }
        }
        score += getScore(len, closed, player == playertomove);
        len = 0, closed = 2;
    }
    return score;
}

int Star(const Board &bd, const int player, const int playertomove) {

    int i = Horizontal(bd, player, playertomove) +
           Vertical(bd, player, playertomove) +
           Sinistral(bd, player, playertomove) +
           Dextral(bd, player, playertomove);

    return std::min(i, INF);
}
}

namespace BoardOp {

    class BoardState {
    public:
        int curplayer;
        Board state;
        std::set<Coordinate> candidates;

        BoardState(): state(board), curplayer(player) {
            for(int i = 0; i < SIZE; i++) {
                for(int j = 0; j < SIZE; j++) {
                    if(board[i][j] == 0)
                    candidates.insert(std::make_pair(i, j));
                }
            }
        }

        BoardState(const BoardState &bs) : curplayer(3 - bs.curplayer), state(bs.state), candidates(bs.candidates) {} //null move
        BoardState(const BoardState &bs, const Coordinate &xy) : BoardState(bs) {
            state[xy.first][xy.second] = bs.curplayer;
            candidates.erase(xy);
        }

        int heuristic() {
            using namespace BoardAnal;
            int b = Star(state, 1, curplayer);
            int w = Star(state, 2, curplayer);
            if(curplayer == 1 && b >= INF) return INF;
            if(curplayer == 2 && w >= INF) return -INF;
            return b - w;
        }

        using note = std::vector<int>;
        note prune(int depth, int a, int b) {
            if(depth <= 0 || candidates.empty()) {
                return note({heuristic(), -1, -1});
            }
            if(curplayer == 1) {
                note best = {-INF, -1, -1};
                for(auto i: candidates) {
                    auto newboard = BoardState(*this, i);
                    note tmp = newboard.prune(depth-1, a, b);

                    if(tmp[0] > a) {a = tmp[0];}
                    if(tmp[0] >= b) {return tmp;}
                    if(tmp[0] > best[0]) {
                        best[0] = tmp[0], best[1] = i.first, best[2] = i.second;
                    }
                }
               // std::cout << "best d" << depth << " " << best.first << "(" << best.second.first << ", " << best.second.second << ")\n";
                return best;
            } else {
                note best = {INF, -1, -1};
                for(auto i: candidates) {
                    auto newboard = BoardState(*this, i);
                    note tmp = newboard.prune(depth-1, a, b);

                    if(tmp[0] < b) {b = tmp[0];}
                    if(tmp[0] <= b) {return tmp;}
                    if(tmp[0] < best[0]) {
                        best[0] = tmp[0], best[1] = i.first, best[2] = i.second;
                    }
                }

               // std::cout << "best d" << depth << " " << best.first << "(" << best.second.first << ", " << best.second.second << ")\n";
                return best;
            }

        }
    };

}



void read_board(std::ifstream& fin) {
    fin >> player;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            fin >> board[i][j];
        }
    }
}

void write_valid_spot(std::ofstream& fout) {
    if(board[SIZE/2][SIZE/2] == 0) {
        fout << SIZE/2 << " " << SIZE/2 << std::endl;
        fout.flush();
        return;
    }
    int x, y;
    BoardOp::BoardState rushia;
    auto ans = rushia.prune(3, -INF, INF);
    std::cout << ans[1] << " " << ans[2] << std::endl;
    fout << ans[1] << " " << ans[2] << std::endl;
    fout.flush();
    // Keep updating the output until getting killed.
}

int main(int, char** argv) {
    std::ifstream fin(argv[1]);
    std::ofstream fout(argv[2]);
    read_board(fin);
    write_valid_spot(fout);
    fin.close();
    fout.close();
    return 0;
}
