//
// Created by laccs on 5/9/2022.
//

#ifndef SAKK_GAMEDATA_HPP
#define SAKK_GAMEDATA_HPP

#include "Enums.hpp"

class Game;
class GameMenu;
class Board;

class GameData {
public:
    static const int BOARD_SIZE = 8;

private:
    Type _boardType[BOARD_SIZE][BOARD_SIZE];
    Side _boardSide[BOARD_SIZE][BOARD_SIZE];

    Side _sideToMove = WHITE;

    bool _checkWhite = false;
    bool _checkBlack = false;
    bool _gameOver = false;

    friend Game;
    friend GameMenu;
    friend Board;
};


#endif //SAKK_GAMEDATA_HPP
