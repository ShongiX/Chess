//
// Created by laccs on 5/9/2022.
//

#ifndef SAKK_CONTROLLER_HPP
#define SAKK_CONTROLLER_HPP

class Game;
class GameMenu;
class GameData;

class Controller {
    Game* _game{};
    GameMenu* _gameMenu{};

    GameData* _gd{};

public:
    Controller(Game* game, GameMenu* gameMenu);

    void getInfo();
    void sendInfo();
};


#endif //SAKK_CONTROLLER_HPP
