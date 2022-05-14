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

    bool checkLine(GameData gd, int x, int y, int dx, int dy);
    bool checkDiag(GameData gd, int x, int y, int dx, int dy);
    bool canMove(GameData gd, int x, int y, int dx, int dy);
    //bool isPinned(GameData gd, int x, int y, int dx, int dy);
    bool isAttacked(GameData gd, int dx, int dy);
    void move(int x, int y, int dx, int dy);
    void move(GameData gd, int x, int y, int dx, int dy);
    Side check(GameData gd);

    bool overallCheck(GameData gd, int x, int y, int dx, int dy);
};


#endif //SAKK_GAME_HPP
