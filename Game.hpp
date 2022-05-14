//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_GAME_HPP
#define SAKK_GAME_HPP

#include <vector>
#include <functional>
#include "GameData.hpp"

struct Move {
    int x{}, y{};
    int dx{}, dy{};

    Side s, ds;
    Type t, dt;

    bool saved = false;
};

class Game {
    //std::function<void()> _deadFunction = std::function<void()>();

    GameData* _gd{};
    Move lastMove;

    bool checkLine(int x, int y, int dx, int dy);
    bool checkDiag(int x, int y, int dx, int dy);
    bool canMove(int x, int y, int dx, int dy);
    void check();
    bool isAttacked(int dx, int dy, Side attackedBy);
    void saveMove(int x, int y, int dx, int dy);
public:
    Game();
    GameData* getInfo();
    void update();

    void move(int x, int y, int dx, int dy);
    void unmove();
    bool overallCheck(int x, int y, int dx, int dy);

    void checkGameOver();

    //void setFunc(const std::function<void()>& dead);
};


#endif //SAKK_GAME_HPP
