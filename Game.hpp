//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_GAME_HPP
#define SAKK_GAME_HPP


#include <vector>
#include "Tile.hpp"

const int BOARD_SIZE = 8;

class GameData {
    std::vector<std::vector<Tile>> _board;

    friend Game;
};

class Game {
    GameData* _gd{};

public:
    Game();
};


#endif //SAKK_GAME_HPP
