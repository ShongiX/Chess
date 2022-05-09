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
    GameData* getInfo();

    void update();

    bool checkLine(int x, int y, int dx, int dy);
    bool checkDiag(int x, int y, int dx, int dy);
    bool canMove(int x, int y, int dx, int dy);
    void move(int x, int y, int dx, int dy);
};


#endif //SAKK_GAME_HPP
