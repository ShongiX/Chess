//
// Created by laccs on 5/9/2022.
//

#include "Controller.hpp"
#include "Game.hpp"
#include "Menu.hpp"

Game* Controller::_game{};
GameMenu* Controller::_gameMenu{};
GameData* Controller::_gd{};

Controller::Controller() = default;

void Controller::init(Game* game, GameMenu* gameMenu) {
    _game = game;
    _gameMenu = gameMenu;
    _gd = _game->getInfo();
}

void Controller::getInfo() {
    _gd = _game->getInfo();
}

void Controller::sendInfo() {
    _gameMenu->setInfo(_gd);
}

bool Controller::askIfCanMove(int x, int y, int dx, int dy) {
    return _game->overallCheck(x,y,dx,dy);
}

void Controller::move(int x, int y, int dx, int dy) {
    _game->move(x,y,dx,dy);
    _game->checkGameOver();
}

void Controller::promote(Side sideToMove) {
    _gameMenu->_promote(sideToMove);
}

void Controller::promote(Type typeChosen) {
    _game->promotePawn(typeChosen);
}
