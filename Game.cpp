//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"

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
