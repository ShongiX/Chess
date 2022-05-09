//
// Created by laccs on 5/6/2022.
//

#include "System.hpp"
#include "Menu.hpp"
#include "Button.hpp"
#include "Text.hpp"
#include "Piece.hpp"
#include "Game.hpp"
#include "Controller.hpp"

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
    init();
}

void System::init() {
    _game = new Game();
    _controller = new Controller(_game,_gameMenu);

    //controller = new Controller(game, gameMenu);
    //game->setFunc([&](){ changeState(DEAD); });
    //gameMenu->setController(controller);
}

void System::run() {
    gout.open(_XX,_YY);
    gout << font("../LiberationSans-Regular.ttf",20);
    gin.timer(1000/_FPS);
    int loopCount = 0;

    _activeMenu = _menus[_state];
    _activeMenu->draw(_focus);

    while(gin >> _ev && _ev.keycode != key_escape) {

        _activeMenu->handle(_ev, _focus);

        if (_ev.type == ev_timer) {
            clearWindow::clear(_XX,_YY);

            if (_state == PLAY) {
                //game loop timer
                loopCount++;
                if (loopCount >= _REFRESH && _game) {

                    _controller->getInfo();
                    _controller->sendInfo();

                    _game->update();
                    loopCount = 0;
                }
            }

            _activeMenu->draw(_focus);
            gout << refresh;
        }
    }
}

void System::changeState(State newState) {
    _activeMenu->resetFocus(_focus);
    _focus = -1;

    _state = newState;
    _activeMenu = _menus[newState];
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

    new Sprite(menu,_XX/4,0,"../resources/Title.txt");
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
    _gameMenu = new GameMenu();

    new Board(_gameMenu,0,0,_XX,_YY);

    /*int i = 0; Side s = BLACK;
    new Piece(menu,0*Board::TILE_SIZE, i*Board::TILE_SIZE,ROOK, s);
    new Piece(menu,1*Board::TILE_SIZE, i*Board::TILE_SIZE,BISHOP, s);
    new Piece(menu,2*Board::TILE_SIZE, i*Board::TILE_SIZE,KNIGHT, s);
    new Piece(menu,3*Board::TILE_SIZE, i*Board::TILE_SIZE,QUEEN, s);
    new Piece(menu,4*Board::TILE_SIZE, i*Board::TILE_SIZE,KING, s);
    new Piece(menu,5*Board::TILE_SIZE, i*Board::TILE_SIZE,KNIGHT, s);
    new Piece(menu,6*Board::TILE_SIZE, i*Board::TILE_SIZE,BISHOP, s);
    new Piece(menu,7*Board::TILE_SIZE, i*Board::TILE_SIZE,ROOK, s);

    i = 7, s = WHITE;
    new Piece(menu,0*Board::TILE_SIZE, i*Board::TILE_SIZE,ROOK, s);
    new Piece(menu,1*Board::TILE_SIZE, i*Board::TILE_SIZE,BISHOP, s);
    new Piece(menu,2*Board::TILE_SIZE, i*Board::TILE_SIZE,KNIGHT, s);
    new Piece(menu,3*Board::TILE_SIZE, i*Board::TILE_SIZE,QUEEN, s);
    new Piece(menu,4*Board::TILE_SIZE, i*Board::TILE_SIZE,KING, s);
    new Piece(menu,5*Board::TILE_SIZE, i*Board::TILE_SIZE,KNIGHT, s);
    new Piece(menu,6*Board::TILE_SIZE, i*Board::TILE_SIZE,BISHOP, s);
    new Piece(menu,7*Board::TILE_SIZE, i*Board::TILE_SIZE,ROOK, s);

    for (int j=0; j<8; j++) {
        new Piece(menu,j*Board::TILE_SIZE, 1*Board::TILE_SIZE,PAWN, BLACK);
        new Piece(menu,j*Board::TILE_SIZE, 6*Board::TILE_SIZE,PAWN, WHITE);
    }*/
    return _gameMenu;
}











