//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"
#include <cstdlib>

Game::Game() {
    _gd = new GameData();

    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            _gd->_boardType[i][j] = NONE;
            _gd->_boardSide[i][j] = EITHER;
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
    _gd->_boardType[1][i] = BISHOP;
    _gd->_boardType[2][i] = KNIGHT;
    _gd->_boardType[3][i] = QUEEN;
    _gd->_boardType[4][i] = KING;
    _gd->_boardType[5][i] = KNIGHT;
    _gd->_boardType[6][i] = BISHOP;
    _gd->_boardType[7][i] = ROOK;

    i = 7;
    _gd->_boardType[0][i] = ROOK;
    _gd->_boardType[1][i] = BISHOP;
    _gd->_boardType[2][i] = KNIGHT;
    _gd->_boardType[3][i] = QUEEN;
    _gd->_boardType[4][i] = KING;
    _gd->_boardType[5][i] = KNIGHT;
    _gd->_boardType[6][i] = BISHOP;
    _gd->_boardType[7][i] = ROOK;

    for (int j=0; j<8; j++) {
        _gd->_boardType[j][1] = PAWN;
        _gd->_boardType[j][6] = PAWN;
    }
}

void Game::update() {}

GameData *Game::getInfo() {
    return _gd;
}

bool Game::checkLine(int x, int y, int dx, int dy) {
    if (x == dx) {
        if (y - dy > 0) {
            for (int i = y-1; i != dy; i--) if(_gd->_boardType[i][dx] != NONE) return false;
        } else {
            for (int i = y+1; i != dy; i++) if(_gd->_boardType[i][dx] != NONE) return false;
        }
    }
    else if (y == dy) {
        if (x - dx > 0) {
            for (int i = x-1; i != dx; i--) if(_gd->_boardType[dy][i] != NONE) return false;
        } else {
            for (int i = x+1; i != dx; i++) if(_gd->_boardType[dy][i] != NONE) return false;
        }
    }

    return true;
}

bool Game::checkDiag(int x, int y, int dx, int dy) {
    if(x - dx > 0 && y - dy > 0) {

        int j = x-1;
        int i = y-1;

        while(i != dy) {
            if (_gd->_boardType[i][j] != NONE) return false;

            i--;
            j--;
        }
    } else if (x - dx < 0 && y - dy < 0) {

        int j = x+1;
        int i = y+1;

        while (i != dy) {

            if (_gd->_boardType[i][j] != NONE) return false;

            i++;
            j++;
        }
    } else if (x - dx > 0 && y - dy < 0) {

        int j = x-1;
        int i = y+1;

        while (i != dy) {

            if (_gd->_boardType[i][j] != NONE) return false;

            i++;
            j--;
        }
    } else if (x - dx < 0 && y - dy > 0) {

        int j = x+1;
        int i = y-1;

        while (i != dy) {

            if (_gd->_boardType[i][j] != NONE) return false;

            i--;
            j++;
        }
    }

    return true;
}

bool Game::canMove(int x, int y, int dx, int dy) {
    Type t = _gd->_boardType[x][y];
    Side s = _gd->_boardSide[x][y];

    //check if King is in check is missing
    if (_gd->_boardSide[dx][dy] == s) return false;
    else {
        if (t == QUEEN) {
            if (abs(x-dx) != abs(y-dy)) return false;
            return checkDiag(x,y,dx,dy) && checkLine(x,y,dx,dy);
        }
    }
    return false;
}
