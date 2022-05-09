//
// Created by laccs on 5/9/2022.
//

#ifndef SAKK_GAMEDATA_HPP
#define SAKK_GAMEDATA_HPP

#include "Enums.hpp"

class Game;

class GameData {
public:
    static const int BOARD_SIZE = 8;

private:
    Type _boardType[BOARD_SIZE][BOARD_SIZE];
    Side _boardSide[BOARD_SIZE][BOARD_SIZE];

    friend Game;
};


#endif //SAKK_GAMEDATA_HPP
