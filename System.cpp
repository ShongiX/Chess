//
// Created by laccs on 5/6/2022.
//

#include "System.hpp"
#include "Menu.hpp"

using namespace genv;

System::System(int XX, int YY, int FPS) : _XX(XX), _YY(YY), _FPS(FPS) {

}

void System::changeState(State newState) {
    _state = newState;
    _activeMenu = _menus[newState];
}

void System::run() {
    gout.open(_XX,_YY);
    gout << font("../LiberationSans-Regular.ttf",20);
    gin.timer(1000/_FPS);

    _activeMenu = _menus[_state];

    //int loopCount = 0;

    while(gin >> _ev && _ev.keycode != key_escape) {

        if (_activeMenu) _activeMenu->handle(_ev);

        if (_ev.type == ev_timer) {
            /*clearWindow();

            if (_state == PLAY) {
                //game loop timer
                loopCount++;
                if (loopCount >= REFRESH && game) {
                    if (controller) {
                        controller->getInfo();
                        controller->sendInfo();
                    }

                    game->update();
                    loopCount = 0;
                }
            } else if (_state == DEAD) {
                score = game->getScore();
                highScore = game->getHighScore();
                printScore();
            }*/

            if (_activeMenu) _activeMenu->draw();
            gout << refresh;
        }
    }
}