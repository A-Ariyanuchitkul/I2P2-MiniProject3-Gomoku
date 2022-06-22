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
const int INF = std::numeric_limits<int>::max()/16; //To prevent overflow
const int MAXDEPTH = 8;



using Board = std::array<std::array<int, SIZE>, SIZE>;
using Coordinate = std::pair<int, int>;

int player;
Board board;

namespace BoardAnal {
/*
const std::vector<unsigned long long> _btmp = { //for hashing
0x4dc91d376be22658,0x8bcf74953f6d0a87,0x79e50e528a1fca28,0x889e2d143ea8b6d9,0x972c830f1d65998d,0x10820ba2a3a9857a,0x7a4d667687b2725c,0xc33b60b8ee7b07b9,0x86f1ecc7ef509845,
0x7006c9650c59ecdd,0xbaf8d6836651c26e,0x7d96df2ecff24dac,0xdac4e148d08bd621,0x5deadac85c7b1f91,0x1e5d113bdd71173e,0x31d8b5d4017b6ff5,0x3acfa45f6ef02731,0x43b410dd0994f80f,
0xf739edae51689e66,0x867e4c3f3ec2d95c,0xb6a047d19b1a7a78,0xaa707d3b90e79600,0x6f4874967a5c7bf1,0x14b3e0fdeb6194a3,0x03df8b14d1e6a8fe,0x370502d9e49f9d31,0x9400a46de3e5acde,
0x9ddfadea7580986f,0x113f5320bca1ae67,0xdbc7b277b32e2f75,0xc5a4d49fee0f5f51,0xaab3ae13010d3c66,0x4a85c6b4265a984d,0x370f4877ba096936,0xca73d3130f814213,0x9229b3b310a382fb,
0x7998960a3b54e4e4,0x107967411aca3ffe,0xcd3abf263ac87148,0x7bde4e919eab74b1,0xd6b27b36e3602994,0x45a3f34745a42e32,0x149027136e5ca9f6,0xcdda297c9a2dc660,0xf73f4dd9761098cc,
0x1ec2c87c02d0f46d,0x26d509858aa72820,0xf505aaeeea4d02ff,0x1f5d5818d2df96e1,0x9e741684fbd8a303,0xbd208210357a28d9,0xd9495397e822a653,0xd0c6a0232e2d04ad,0x9bef2ef74fd96d27,
0x55fa0ad7114e3d31,0x2cf40f9c2df29cbc,0x576a8a6510dab527,0x5d76d1c0e3e1f3a4,0x01084028c15456ed,0x4b8b955493b21dd9,0x14966d5eba9d83f2,0xa69c7244c47483a1,0x6a4941e758874e71,
0x8e07d62384e79615,0xf5f057d9d541e92c,0xa6faa158e718630f,0x8edeff32994f9414,0x9e3f9081ef2743ed,0xe7207116e0d1ba71,0xb49bb8c7f72be04d,0x94bab24a42e000a6,0x0e44e401660cfb97,
0x7d33ea41279c67a7,0x57a63abf0448a10d,0x4c49a2f11927bb63,0x0b0c321beb120a11,0xfe2f88d5fa0a8ec3,0x19dc35afa9c67ce7,0xb4680b5ae4dba07c,0x72a5fd6a1e11de3c,0x8291ffb0a8f9e2ab,
0x9f2165f7b6530d90,0xd0b6c55d5c647645,0x19a290d81e95c18a,0xe2d25f233548a25b,0xc573cc82f8936ee7,0x96051360869c684a,0xf6eb7cdfb5e6f6cd,0x6ddd6d481681f55f,0x341db0793572ef7f,
0x59f25a236c44a1ef,0x93a512067966372f,0x9f373b7e40a06a81,0xb1b476ccc02f42b4,0xb135b0f993b7d48e,0xa2fa473473769082,0x6168493dd1c385ea,0xea218a2bf4313052,0xcab5388951b4d5ba,
0x0c492c69b89a533d,0x7296bfc8548533a1,0xcf6926bb77a06e27,0x8db80a7e218c8fd6,0xacc8980354118c38,0x5b7782efa5cba041,0x4165e474d5817dce,0x7ef436a9749865b5,0x1c052af26a03005f,
0x36d7594d4be0ea1d,0xac734bbb144c9b00,0x954aed175e6cad5a,0xc5c9b086cab377ed,0xedb83c1c769374dc,0x20e2dd71f084c21b,0xfebbc6d13bb4554f,0x831e906b33df44d9,0xba5bbad184f38ff5,
0x32a0c1cd5bf4335b,0xc7e8b9462b5f52d7,0x1cf5ba63569c4d78,0xbebc23aee9da4256,0x403867a918eaa91a,0x37f086796f809369,0xac6c201a1acaef5a,0x88d76c11c8f76bfd,0x1f52df66f2eaf0d3,
0x0ca1d1b55e5bcdf5,0x47b5905083f54a6a,0x931d15f1f9fff988,0x43b12a74738a5317,0x8aed0847ba4ee5ae,0xe36dcf46f6531723,0xfa821c9fb9d343dd,0x5fb3c0eb63cb5b59,0x60387e9ce26809d2,
0xad612c80dee88454,0xf62685541d46ef66,0xca669c40f4fd77d4,0x3036a51fcd181bdd,0x421f9b807ed5aa2b,0x1d754307a46795b4,0xc27cb11d6a830a3a,0x68721d2ccf735bf4,0xca7a3776de539981,
0x382c8fe7dd5e7daa,0x85b43057bc8cd928,0xc61c23e64f162791,0x8f7b1a8a0db5a783,0x21400da2e4003340,0x6118eedf91417c34,0x4da388a88156f106,0x8b538b78bae34ed9,0xd6f2a70f9b38a4cd,
0x5cb371a957e31761,0xab70a053f36603ce,0x4b48921edf374123,0x45cb1b2c9cab5f2e,0xec9c176f4163d315,0xfc3d73a15f742798,0x02a6e221a212b130,0xfc2190cab6370d64,0xb0f0aaa4854f2d59,
0xe40968da4e8bbb6c,0x12475b3c9b96de0f,0x3f400fb0c77aef71,0xba586558fd1a4e46,0x66d66e6838dd8921,0x81bb0ba5e99756f6,0x7ea849196093d892,0x113939ab44b75fe0,0x9fd0da4e5c87c785,
0xb496dfec0c445486,0x460669cc873432d0,0x267d79fbb8a04f09,0x70159447efcd2cf3,0x3b4642f1022c8a09,0xfde54092fdd72a23,0xb7e9bcd62d85fd8a,0x61a2319b4e9d307c,0x5cc762809e933a98,
0xf7e43ebcb3de9f0d,0xd2c04262b413f0af,0x047fb2c63371d091,0x871bbead6781cc8a,0xaf4aeca74a801a67,0x61f127eeaa5eecf9,0x8ed928c29b4e58d5,0x065d3dde10c3d1fd,0x67d69e1d78ea0285,
0xde3519875c0ef5eb,0xbca08da9b2bb90d7,0x9a0ad0f92d980f38,0x406695d262cec330,0xeb69caef78ba76da,0xffc969752c474367,0x438922eef3bf510b,0xab7a65630c34f0f4,0xc96d8ec9b1fe6462,
0x70da18ef5624d4fb,0xdc09723e2827226b,0x7fe74dfcfa778bb6,0xd32f6883b533d7db,0xe68133c5d5e4dcf6,0xe143381a0c4e254a,0xd71d6abf51ef78a4,0x633a9112d5f3c60b,0xbeb730be0fae7bc2,
0x2eaa3d36216ed308,0x8b87d57922f81efc,0x222b1495d0e3b628,0x29306ad09d0c77a8,0x406ae67950a355df,0x72fdb5f1e18d614c,0x72fe8a072c77a0f6,0x242777b058a7fc34,0x527ef4baac358bcc,
0xf349716c9cfa92ab,0x7193d3b81f359354,0xcb2ee4e70934baa4,0x1fc6330d4e001dca,0xfd0c8ddeabe588bd,0x517a5fe64aea4ebc,0x48aa915be737ad53,0xde16916faccec9d1,0x93c1ff37d9ff3226};
std::unordered_map<unsigned long long, int> eval_map;
*/


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

int heuristic(Board state, int curplayer) {
    int b = Star(state, 1, curplayer);
    int w = Star(state, 2, curplayer);
    if(curplayer == 1 && b >= INF) return INF;
    if(curplayer == 2 && w >= INF) return -INF;
    return b - w;
}

}

namespace BoardOp {

    using namespace BoardAnal;

    class BoardState {
    public:
        int curplayer;
        Board state;
        Coordinate lastmove;

        std::set<BoardState> candidates;

        BoardState(): state(board), curplayer(player), lastmove(std::make_pair(-1, -1)) {}
        BoardState(const BoardState &bs) : curplayer(3 - bs.curplayer), state(bs.state), lastmove(std::make_pair(-1, -1)) {} //null move
        BoardState(const BoardState &bs, const Coordinate &xy) : curplayer(3 - bs.curplayer), state(bs.state), lastmove(xy){
            state[xy.first][xy.second] = bs.curplayer;
        }

        void load() {
            for(int i = 0; i < SIZE; i++) for(int j = 0; j < SIZE; j++) {
                if(state[i][j] == 0) {

                    BoardState tmp(*this, std::make_pair(i, j));
                    std::cout << tmp.lastmove.first << "&" << tmp.lastmove.second << "\n";
                    candidates.insert(tmp);
                }
            }
            for(auto i: candidates)

            std::cout << "\n";
        }

        using note = std::vector<int>;
        note prune(int depth, int a, int b) {
            load();
            if(depth <= 0 || candidates.empty()) {
                    std::cout << "h" << heuristic(state, curplayer);
                return note({heuristic(state, curplayer), lastmove.first, lastmove.second});
            }
            if(curplayer == 1) {
                note best = {-INF, -1, -1};
                for(auto i: candidates) {
                    std::cout << "huh";
                    note tmp = i.prune(depth-1, a, b);
                    if(best[0] < tmp[0]) {
                        best[0] = tmp[0], best[1] = i.lastmove.first, best[2] = i.lastmove.second;
                    }
                    if(a < tmp[0]) {a = tmp[0];}
                    if(tmp[0] >= b) {return tmp;}
                }
                return best;
            } else {
                note best = {INF, -1, -1};
                for(auto i: candidates) {
                    note tmp = i.prune(depth-1, a, b);
                    if(best[0] > tmp[0]) {
                        best[0] = tmp[0], best[1] = i.lastmove.first, best[2] = i.lastmove.second;
                    }
                    if(b > tmp[0]) {b = tmp[0];}
                    if(tmp[0] <= b) {return tmp;}
                }
                return best;
            }

        }

                bool operator < (const BoardState& a) const {
                    if(curplayer == 1) return heuristic(state, 1) > heuristic(a.state, 1);
                    else return heuristic(state, 2) < heuristic(a.state, 2);
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
