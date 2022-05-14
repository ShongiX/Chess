//
// Created by laccs on 5/9/2022.
//

#ifndef SAKK_CONTROLLER_HPP
#define SAKK_CONTROLLER_HPP

class Game;
class GameMenu;
class GameData;

class Controller {
    static Game* _game;
    static GameMenu* _gameMenu;
    static GameData* _gd;

public:
    Controller();

    static void init(Game* game, GameMenu* gameMenu);

    static void getInfo();
    static void sendInfo();

    static bool askIfCanMove(int x, int y, int dx, int dy);
    static void move(int x, int y, int dx, int dy);
    static void unmove();
};


#endif //SAKK_CONTROLLER_HPP
