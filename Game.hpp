//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_GAME_HPP
#define SAKK_GAME_HPP

#include <vector>
#include "GameData.hpp"

class Game {
    GameData* _gd{};

public:
    Game();
    void update();

    GameData* getInfo();
};


#endif //SAKK_GAME_HPP
