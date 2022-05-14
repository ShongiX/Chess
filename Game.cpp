//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"
#include "Piece.hpp"
#include <cstdlib>
#include <iostream>

Game::Game() {
    _gd = new GameData();

    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            _gd->_boardType[i][j] = NONE;
            _gd->_boardSide[i][j] = NEITHER;
        }
    }

    for (int i=0; i<GameData::BOARD_SIZE; ++i) {
        _gd->_boardSide[i][0] = BLACK;
        _gd->_boardSide[i][1] = BLACK;
        _gd->_boardSide[i][6] = WHITE;
        _gd->_boardSide[i][7] = WHITE;
    }

    int i=0;
    _gd->_boardType[0][i] = ROOK;
    _gd->_boardType[1][i] = KNIGHT;
    _gd->_boardType[2][i] = BISHOP;
    _gd->_boardType[3][i] = QUEEN;
    _gd->_boardType[4][i] = KING;
    _gd->_boardType[5][i] = BISHOP;
    _gd->_boardType[6][i] = KNIGHT;
    _gd->_boardType[7][i] = ROOK;

    i = 7;
    _gd->_boardType[0][i] = ROOK;
    _gd->_boardType[1][i] = KNIGHT;
    _gd->_boardType[2][i] = BISHOP;
    _gd->_boardType[3][i] = QUEEN;
    _gd->_boardType[4][i] = KING;
    _gd->_boardType[5][i] = BISHOP;
    _gd->_boardType[6][i] = KNIGHT;
    _gd->_boardType[7][i] = ROOK;

    for (int j=0; j<GameData::BOARD_SIZE; j++) {
        _gd->_boardType[j][1] = PAWN;
        _gd->_boardType[j][6] = PAWN;
    }
}

GameData *Game::getInfo() {
    return _gd;
}

void Game::update() {}

bool Game::checkLine(GameData gd, int x, int y, int dx, int dy) {
    if (x == dx) {
        if (y - dy > 0) {
            for (int i = y-1; i != dy; i--) if(gd._boardType[dx][i] != NONE) return false;
        } else {
            for (int i = y+1; i != dy; i++) if(gd._boardType[dx][i] != NONE) return false;
        }
    }
    else if (y == dy) {
        if (x - dx > 0) {
            for (int i = x-1; i != dx; i--) if(gd._boardType[i][dy] != NONE) return false;
        } else {
            for (int i = x+1; i != dx; i++) if(gd._boardType[i][dy] != NONE) return false;
        }
    }

    return true;
}

bool Game::checkDiag(GameData gd, int x, int y, int dx, int dy) {
    int k,l;
    if (x-dx > 0) k = -1;
    else k = 1;

    if (y-dy > 0) l = -1;
    else l = 1;

    for (int i = x+k; i != dx;) {
        for (int j = y+l; j != dy ;) {
            if (gd._boardType[i][j] != NONE) return false;

            i+=k;
            j+=l;
        }
    }
    return true;
}

bool Game::overallCheck(GameData gd, int x, int y, int dx, int dy) {
    if (!canMove(gd,x,y,dx,dy)) return false;

    move(gd,x,y,dx,dy);
    Side checked = check(gd);


    if (checked == gd._sideToMove) return false;

    return true;
}

bool Game::canMove(GameData gd, int x, int y, int dx, int dy) {
    Type t = gd._boardType[x][y];
    Side s = gd._boardSide[x][y];

    //std::cout << s << " " << t << " ";
    //printf("Attempted move from %d,%d to %d,%d\n",x,y,dx,dy);

    //FIXME: doesn't check whether piece is pinned

    if (gd._boardSide[dx][dy] == s) return false;
    else {
        if (t == QUEEN) {
            if (x == dx || y == dy) return checkLine(*_gd,x,y,dx,dy);
            if (abs(x-dx) == abs(y-dy)) return checkDiag(*_gd,x,y,dx,dy);
        } else if (t == ROOK) {
            if (x != dx && y != dy) return false;
            return checkLine(*_gd,x,y,dx,dy);
        } else if (t == KNIGHT) {
            if ((x - dx) * (x - dx) + (y - dy) * (y - dy) == 5) return true;
        } else if (t == BISHOP) {
            if (abs(x-dx) != abs(y-dy)) return false;
            return checkDiag(*_gd,x,y,dx,dy);
        } else if (t == PAWN) {
            if (s == WHITE) {
                if (x == dx && dy-y == -1 && gd._boardType[dx][dy] == NONE) return true; //if one forward, no piece at destination
                if (x == dx && dy-y == -2 && y == 6 && gd._boardType[dx][y-1] == NONE && gd._boardType[dx][dy] == NONE) return true; //if two forward, initial place and no piece at destination
                if (abs(x-dx) == 1 && dy-y == -1 && gd._boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                return false;
            } else {
                if (x == dx && dy-y == 1 && gd._boardType[dx][dy] == NONE) return true; //if one forward, no piece at destination
                if (x == dx && dy-y == 2 && y == 1 && gd._boardType[dx][y+1] == NONE && gd._boardType[dx][dy] == NONE) return true; //if two forward, initial place and no piece at destination
                if (abs(x-dx) == 1 && dy-y == 1 && gd._boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                return false;
            }
        } else { //KING
            if (abs(x-dx) <= 1 && abs(y-dy) <= 1) return true;
        }
    }
    return false;
}

//FIXME: Not working
/*bool Game::isPinned(GameData gd, int x, int y, int dx, int dy) {
    gd._boardType[dx][dy] = gd._boardType[x][y];
    gd._boardSide[dx][dy] = gd._boardSide[x][y];

    gd._boardType[x][y] = NONE;
    gd._boardSide[x][y] = NEITHER;

    //move(gd,x,y,dx,dy);
    //return true;
    return check(gd);
}*/

bool Game::isAttacked(GameData gd, int dx, int dy) {
    for (int i=0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (gd._boardSide[i][j] != gd._sideToMove && gd._boardSide[i][j] != NEITHER) {
                if (canMove(gd,i,j,dx,dy)) return true;
            }
        }
    }
    return false;
}

void Game::move(int x, int y, int dx, int dy) {
    _gd->_boardType[dx][dy] = _gd->_boardType[x][y];
    _gd->_boardSide[dx][dy] = _gd->_boardSide[x][y];

    _gd->_boardType[x][y] = NONE;
    _gd->_boardSide[x][y] = NEITHER;

    if (_gd->_sideToMove == WHITE) _gd->_sideToMove = BLACK;
    else _gd->_sideToMove = WHITE;

    Side checked = check(*_gd);
    if (checked == WHITE) {
        _gd->_checkWhite = true;
    } else if (checked == BLACK) {
        _gd->_checkBlack = true;
    }
}

void Game::move(GameData gd, int x, int y, int dx, int dy) {
    gd._boardType[dx][dy] = gd._boardType[x][y];
    gd._boardSide[dx][dy] = gd._boardSide[x][y];

    gd._boardType[x][y] = NONE;
    gd._boardSide[x][y] = NEITHER;

    //change turn
    //if (gd._sideToMove == WHITE) gd._sideToMove = BLACK;
    //else gd._sideToMove = WHITE;
}

Side Game::check(GameData gd) {
    int wx,wy;
    int bx,by;

    for (int i=0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (gd._boardType[i][j] == KING) {
                if (gd._boardSide[i][j] == WHITE) {
                    wx = i;
                    wy = j;
                } else {
                    bx = i;
                    by = j;
                }
            }
        }
    }

    if (isAttacked(gd,wx,wy)) {
        std::cout << "Feher sakkban van\n";
        return WHITE;
    } else if (isAttacked(gd,bx,by)) {
        std::cout << "Fekete sakkban van\n";
        return BLACK;
    }
    return NEITHER;

}


