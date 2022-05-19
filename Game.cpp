//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"
#include "Board.hpp"
#include "Controller.hpp"
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

void Game::update() {
    if (!promotionCalled) {
        for (auto & i : _gd->_boardType) {
            if (i[0] == PAWN) {
                Controller::promote(WHITE);
                promotionCalled = true;
            }
            if (i[7] == PAWN) {
                Controller::promote(BLACK);
                promotionCalled = true;
            }
        }
    }
}

bool Game::checkLine(int x, int y, int dx, int dy) {
    if (x == dx) {
        if (y - dy > 0) {
            for (int i = y-1; i != dy; i--) if(_gd->_boardType[dx][i] != NONE) return false;
        } else {
            for (int i = y+1; i != dy; i++) if(_gd->_boardType[dx][i] != NONE) return false;
        }
    }
    else if (y == dy) {
        if (x - dx > 0) {
            for (int i = x-1; i != dx; i--) if(_gd->_boardType[i][dy] != NONE) return false;
        } else {
            for (int i = x+1; i != dx; i++) if(_gd->_boardType[i][dy] != NONE) return false;
        }
    }

    return true;
}

bool Game::checkDiag(int x, int y, int dx, int dy) {
    int k,l;
    if (x-dx > 0) k = -1;
    else k = 1;

    if (y-dy > 0) l = -1;
    else l = 1;

    for (int i = x+k; i != dx;) {
        for (int j = y+l; j != dy ;) {
            if (_gd->_boardType[i][j] != NONE) return false;

            i+=k;
            j+=l;
        }
    }
    return true;
}

bool Game::canMove(int x, int y, int dx, int dy) {
    Type t = _gd->_boardType[x][y];
    Side s = _gd->_boardSide[x][y];

    if (_gd->_boardSide[dx][dy] == s) return false;
    else {
        if (t == QUEEN) {
            if (x == dx || y == dy) return checkLine(x,y,dx,dy);
            if (abs(x-dx) == abs(y-dy)) return checkDiag(x,y,dx,dy);
        } else if (t == ROOK) {
            if (x != dx && y != dy) return false;
            return checkLine(x,y,dx,dy);
        } else if (t == KNIGHT) {
            if ((x - dx) * (x - dx) + (y - dy) * (y - dy) == 5) return true;
        } else if (t == BISHOP) {
            if (abs(x-dx) != abs(y-dy)) return false;
            return checkDiag(x,y,dx,dy);
        } else if (t == PAWN) {
            if (s == WHITE) {
                if (x == dx && dy-y == -1 && _gd->_boardType[dx][dy] == NONE) return true; //if one forward, no piece at destination
                if (x == dx && dy-y == -2 && y == 6 && _gd->_boardType[dx][y-1] == NONE && _gd->_boardType[dx][dy] == NONE) {
                    //if ( (x-1>=0 && _gd->_boardSide[dx-1][dy] == BLACK && _gd->_boardType[dx-1][dy] == PAWN) || (x+1<=GameData::BOARD_SIZE && _gd->_boardSide[dx+1][dy] == BLACK && _gd->_boardType[dx+1][dy] == PAWN) ) _gd->_enPassant = true;
                    return true; //if two forward, initial place and no piece at destination
                }
                if (abs(x-dx) == 1 && dy-y == -1 && _gd->_boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                //if (abs(x-dx) == 1 && dy-y == -1 && _gd->_enPassant && _gd->_boardType[dx][y] == PAWN) return true; //en passant
                return false;
            } else {
                if (x == dx && dy-y == 1 && _gd->_boardType[dx][dy] == NONE) return true; //if one forward, no piece at destination
                if (x == dx && dy-y == 2 && y == 1 && _gd->_boardType[dx][y+1] == NONE && _gd->_boardType[dx][dy] == NONE) {
                    //if ( (x-1>=0 && _gd->_boardSide[dx-1][dy] == WHITE && _gd->_boardType[dx-1][dy] == PAWN) || (x+1<=GameData::BOARD_SIZE && _gd->_boardSide[dx+1][dy] == BLACK && _gd->_boardType[dx+1][dy] == PAWN) ) _gd->_enPassant = true;
                    return true; //if two forward, initial place and no piece at destination
                }
                if (abs(x-dx) == 1 && dy-y == 1 && _gd->_boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                //if (abs(x-dx) == 1 && dy-y == 1 && _gd->_boardType[x][dy] == PAWN && _gd->_enPassant) return true; //en passant
                return false;
            }
        } else { //KING
            if (abs(x-dx) <= 1 && abs(y-dy) <= 1) return true;
        }
    }
    return false;
}

void Game::check() {
    int wx,wy;
    int bx,by;

    for (int i = 0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardType[i][j] == KING) {
                if (_gd->_boardSide[i][j] == WHITE) {
                    wx = i;
                    wy = j;
                } else {
                    bx = i;
                    by = j;
                }
            }
        }
    }

    if (isAttacked(wx,wy,BLACK)) {
        _gd->_checkWhite = true;
    } else {
        _gd->_checkWhite = false;
    }

    if (isAttacked(bx,by,WHITE)) {
        _gd->_checkBlack = true;
    } else {
        _gd->_checkBlack = false;
    }
}

bool Game::isAttacked(int dx, int dy,Side attackedBy) {
    for (int i = 0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardSide[i][j] == attackedBy) {
                if (canMove(i,j,dx,dy)) return true;
            }
        }
    }
    return false;
}

void Game::saveMove(int x, int y, int dx, int dy) {
    lastMove.saved = true;
    lastMove.x = x;
    lastMove.y = y;
    lastMove.dx = dx;
    lastMove.dy = dy;
    lastMove.s = _gd->_boardSide[x][y];
    lastMove.ds = _gd->_boardSide[dx][dy];
    lastMove.t = _gd->_boardType[x][y];
    lastMove.dt = _gd->_boardType[dx][dy];
}

void Game::move(int x, int y, int dx, int dy) {
    saveMove(x,y,dx,dy);

    _gd->_boardType[dx][dy] = _gd->_boardType[x][y];
    _gd->_boardSide[dx][dy] = _gd->_boardSide[x][y];

    _gd->_boardType[x][y] = NONE;
    _gd->_boardSide[x][y] = NEITHER;

    if (_gd->_sideToMove == WHITE) _gd->_sideToMove = BLACK;
    else _gd->_sideToMove = WHITE;
}

void Game::unmove() {
    if (!lastMove.saved) return;
    lastMove.saved = false;
    _gd->_boardType[lastMove.x][lastMove.y] = lastMove.t;
    _gd->_boardType[lastMove.dx][lastMove.dy] = lastMove.dt;
    _gd->_boardSide[lastMove.x][lastMove.y] = lastMove.s;
    _gd->_boardSide[lastMove.dx][lastMove.dy] = lastMove.ds;

    if (_gd->_sideToMove == WHITE) _gd->_sideToMove = BLACK;
    else _gd->_sideToMove = WHITE;
}

bool Game::overallCheck(int x, int y, int dx, int dy) {
    if (!canMove(x,y,dx,dy)) return false;

    move(x,y,dx,dy);
    check();
    unmove();

    if (_gd->_sideToMove == WHITE) {
        if (_gd->_checkWhite) return false;
    } else {
        if (_gd->_checkBlack) return false;
    }
    return true;
}

void Game::checkGameOver() {
    bool arePossibleMoves = false;

    for (int i = 0; i<GameData::BOARD_SIZE && !arePossibleMoves; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE && !arePossibleMoves; ++j) {
            if (_gd->_boardSide[i][j] == _gd->_sideToMove) {
                for (int di = 0; di<GameData::BOARD_SIZE && !arePossibleMoves; ++di) {
                    for (int dj = 0; dj < GameData::BOARD_SIZE && !arePossibleMoves; ++dj) {
                        if (i == di && j == dj) continue; //source and destination are the same
                        if (_gd->_boardSide[di][dj] == _gd->_sideToMove) continue; //destination occupied
                        if (overallCheck(i,j,di,dj)) {
                            arePossibleMoves = true;
                        }
                    }
                }
            }
        }
    }

    if (arePossibleMoves) return;

    _gd->_gameOver = true;
    check();
    if (_gd->_checkBlack) {
        std::cout << "White won\n";
        return;
    }
    if (_gd->_checkWhite) {

        std::cout << "Black won\n";
        return;
    }
    std::cout << "The game is a tie\n";
}

void Game::promotePawn(Type typeChosen) {
    promotionCalled = false;
    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        if (_gd->_boardType[i][0] == PAWN) {
            _gd->_boardType[i][0] = typeChosen;
            return;
        }
        if (_gd->_boardType[i][7] == PAWN) {
            _gd->_boardType[i][7] = typeChosen;
            return;
        }
    }
}
