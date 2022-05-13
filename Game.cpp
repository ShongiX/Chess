//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"
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

    //std::cout << s << " " << t << " ";
    //printf("Attempted move from %d,%d to %d,%d\n",x,y,dx,dy);

    //FIXME: doesn't check whether piece is pinned

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
                if (x == dx && dy-y == -2 && y == 6 && _gd->_boardType[dx][y-1] == NONE && _gd->_boardType[dx][dy] == NONE) return true; //if two forward, initial place and no piece at destination
                if (abs(x-dx) == 1 && dy-y == -1 && _gd->_boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                return false;
            } else {
                if (x == dx && dy-y == 1 && _gd->_boardType[dx][dy] == NONE) return true; //if one forward, no piece at destination
                if (x == dx && dy-y == 2 && y == 1 && _gd->_boardType[dx][y+1] == NONE && _gd->_boardType[dx][dy] == NONE) return true; //if two forward, initial place and no piece at destination
                if (abs(x-dx) == 1 && dy-y == 1 && _gd->_boardType[dx][dy] != NONE) return true; //if one diagonal, piece taken
                return false;
            }
        } else { //KING
            if (abs(x-dx) <= 1 && abs(y-dy) <= 1) return true;
        }
    }
    return false;
}

void Game::move(int x, int y, int dx, int dy) {
    _gd->_boardType[dx][dy] = _gd->_boardType[x][y];
    _gd->_boardSide[dx][dy] = _gd->_boardSide[x][y];

    _gd->_boardType[x][y] = NONE;
    _gd->_boardSide[x][y] = NEITHER;
    std::cout << "Move from " << x << "," << y << " to " << dx << "," << dy << "\n";

    //change turn
    if (_gd->_sideToMove == WHITE) _gd->_sideToMove = BLACK;
    else _gd->_sideToMove = WHITE;
}

bool Game::check() {
    int dx, dy;
    for (int i=0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardType[i][j] == KING && _gd->_boardSide[i][j] != _gd->_sideToMove) { //enemy king
                dx = i;
                dy = j;
                break;
            }
        }
    }

    for (int i=0; i<GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardSide[i][j] == _gd->_sideToMove) {
                if (canMove(i,j,dx,dy)) return true;
            }
        }
    }

    return false;
}


