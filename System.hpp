//
// Created by laccs on 5/6/2022.
//

#ifndef SAKK_SYSTEM_HPP
#define SAKK_SYSTEM_HPP

#include <map>
#include "graphics.hpp"

enum State {NONE, MAIN, PLAY, RULES, INFO, CREDITS};

class Menu;

class System {
    const int _XX = 800;
    const int _YY = 800;

    const int _FPS = 25;
    const int _REFRESH = 12; //game loop wait time

    genv::event _ev;
    int _focus = -1;

    Menu* _activeMenu = nullptr;
    std::map<State, Menu*> _menus;
    State _state = MAIN;

    void changeState(State newState);

    void buildMenu();
    Menu* buildMainMenu();
    Menu* buildRulesMenu();
    Menu* buildInfoMenu();
    Menu* buildCreditMenu();
    Menu* buildGameMenu();

public:
    System(int XX, int YY, int FPS);
    void run();
};


#endif //SAKK_SYSTEM_HPP
