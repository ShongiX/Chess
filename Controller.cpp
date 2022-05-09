//
// Created by laccs on 5/9/2022.
//

#include "Controller.hpp"
#include "Game.hpp"
#include "Menu.hpp"

Controller::Controller(Game *game, GameMenu *gameMenu) : _game(game), _gameMenu(gameMenu) {
    _gd = _game->getInfo();
}

void Controller::getInfo() {
    _gd = _game->getInfo();
}

void Controller::sendInfo() {
    _gameMenu->setInfo(_gd);
}
