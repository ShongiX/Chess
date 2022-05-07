//
// Created by laccs on 5/6/2022.
//

#include "System.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "Text.hpp"

using namespace genv;

const int BUTTON_WIDTH = 150;
const int BUTTON_HEIGHT = 70;

class clearWindow : public Widget {
public:
    static void clear(int XX, int YY) {
        gout << color(240,217,181) << move_to(0,0) << box(XX,YY);
    }
};

System::System(int XX, int YY, int FPS) : _XX(XX), _YY(YY), _FPS(FPS) {
    buildMenu();
}

void System::changeState(State newState) {
    _state = newState;
    _activeMenu = _menus[newState];
    _focus = -1;
}

void System::run() {
    gout.open(_XX,_YY);
    gout << font("../LiberationSans-Regular.ttf",20);
    gin.timer(1000/_FPS);

    _activeMenu = _menus[_state];
    _activeMenu->draw(_focus);

    while(gin >> _ev && _ev.keycode != key_escape) {

        if (_activeMenu) _activeMenu->handle(_ev,_focus);

        if (_ev.type == ev_timer) {

            clearWindow::clear(_XX,_YY);
            if (_activeMenu) _activeMenu->draw(_focus);
            gout << refresh;
        }
    }
}

void System::buildMenu() {
    _menus[State::MAIN] = buildMainMenu();
    _menus[State::RULES] = buildRulesMenu();
    _menus[State::INFO] = buildInfoMenu();
    _menus[State::CREDITS] = buildCreditMenu();
    _menus[State::PLAY] = buildGameMenu();
}

Menu* System::buildMainMenu() {
    Menu* menu = new Menu();

    new Sprite(menu,_XX/4,0,"../Title.txt");
    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*0.0,BUTTON_WIDTH,BUTTON_HEIGHT,"Start",[this](){changeState(State::PLAY);});
    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*1.2,BUTTON_WIDTH,BUTTON_HEIGHT,"How to play?",[this](){changeState(State::RULES);});
    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*2.4,BUTTON_WIDTH,BUTTON_HEIGHT,"Info",[this](){changeState(State::INFO);});
    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*3.6,BUTTON_WIDTH,BUTTON_HEIGHT,"Credits",[this](){changeState(State::CREDITS);});
    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*4.8,BUTTON_WIDTH,BUTTON_HEIGHT,"Exit",[](){exit(0);});

    return menu;
}

Menu *System::buildRulesMenu() {
    Menu* menu = new Menu();

    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*0.0,BUTTON_WIDTH,BUTTON_HEIGHT,"Back",[this](){changeState(State::MAIN);});

    return menu;
}

Menu *System::buildInfoMenu() {
    Menu* menu = new Menu();

    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*0.0,BUTTON_WIDTH,BUTTON_HEIGHT,"Back",[this](){changeState(State::MAIN);});

    return menu;
}


Menu *System::buildCreditMenu() {
    Menu* menu = new Menu();

    new Button(menu,_XX/2-BUTTON_WIDTH/2,_YY/4+BUTTON_HEIGHT*0.0,BUTTON_WIDTH,BUTTON_HEIGHT,"Back",[this](){changeState(State::MAIN);});
    new Text(menu,_XX/2,_YY/2,0,0,"Created by: Laccs");

    return menu;
}

Menu *System::buildGameMenu() {
    Menu* menu = new Menu();

    return menu;
}











