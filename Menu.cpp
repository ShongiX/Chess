//
// Created by laccs on 3/13/2022.
//

#include <iostream>
#include "Menu.hpp"
#include "GameData.hpp"
#include "Piece.hpp"
#include "Controller.hpp"
#include "Text.hpp"
#include "Button.hpp"

using namespace genv;

std::vector<int> Board::_underAttackX = std::vector<int>();
std::vector<int> Board::_underAttackY = std::vector<int>();

void Menu::draw(int focus) {
    for (Widget* widget : _widgets) widget->draw();
    if (focus != -1) _widgets[focus]->draw();
}

void Menu::handle(const event& ev, int &focus) {
    if (ev.type == ev_mouse) {
        for (size_t i = 0; i < _widgets.size(); i++) {
            if (_widgets[i]->isFocus(ev) && _widgets[i]->isFocusable()) {
                if (focus != -1 && (signed)i!=focus) _widgets[focus]->setFocus(false);
                focus = (signed)i;
                break;
            }
        }
    }

    if (focus != -1) {
        _widgets[focus]->setFocus(true);
        _widgets[focus]->handle(ev);
    }
}

void Menu::addWidget(Widget *w) {
    _widgets.push_back(w);
}

void Menu::resetFocus(int focus) {
    _widgets.at(focus)->setFocus(false);
}

void GameMenu::handle(const event &ev, int &focus) {
    if (_gd->_gameOver) {
        Menu::handle(ev,focus);
    } else {
        if (ev.type == ev_mouse) {
            int x = ev.pos_x / Board::TILE_SIZE;
            int y = ev.pos_y / Board::TILE_SIZE;

            if (ev.button == btn_left) {
                if (_gd->_boardSide[x][y] == _gd->_sideToMove) { //switching piece
                    if (Board::_activeTileX == x && Board::_activeTileY == y) {
                        Board::_activeTileX = -1;
                        Board::_activeTileY = -1;
                    } else {
                        Board::_activeTileX = x;
                        Board::_activeTileY = y;

                        searchAttackedTiles();
                    }
                } else if (Board::_activeTileX != -1) { //attempting to move
                    if (Controller::askIfCanMove(Board::_activeTileX,Board::_activeTileY,x,y)) {
                        Controller::move(Board::_activeTileX,Board::_activeTileY,x,y);
                        Board::_activeTileX = -1;
                        Board::_activeTileY = -1;
                    }
                }
            }
        } else if (ev.type == ev_key) {
            if (ev.keycode == key_left) {
                Controller::unmove();
            }
        }
    }
}

void GameMenu::build() {
    Widget* tmp_board = _widgets.at(0);
    _widgets.clear();
    _widgets.push_back(tmp_board);
    
    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            Type t = _gd->_boardType[i][j];
            Side s = _gd->_boardSide[i][j];
            
            if (s != NEITHER) {
                
                std::string fileName = "../resources/";
                if (s == WHITE) {
                    if (t == 0) {fileName += "wQ.txt";}
                    else if (t == 1) {fileName += "wR.txt";}
                    else if (t == 2) {fileName += "wN.txt";}
                    else if (t == 3) {fileName += "wB.txt";}
                    else if (t == 4) {fileName += "wP.txt";}
                    else {fileName += "wK.txt";}
                } else {
                    if (t == 0) {fileName += "bQ.txt";}
                    else if (t == 1) {fileName += "bR.txt";}
                    else if (t == 2) {fileName += "bN.txt";}
                    else if (t == 3) {fileName += "bB.txt";}
                    else if (t == 4) {fileName += "bP.txt";}
                    else {fileName += "bK.txt";}
                }
                new Sprite(this,i*Board::TILE_SIZE,j*Board::TILE_SIZE,fileName);
            }
        }
    }

    if (_gd->_gameOver) {
        std::string message = "The game is over. ";
        if (_gd->_checkWhite) message += "Black won!";
        else if (_gd->_checkBlack) message += "White won!";
        else message += "It's a tie!";

        _dead(message);
    }
}

void GameMenu::setInfo(GameData* gd) {
    _gd = gd;
}

void GameMenu::searchAttackedTiles() {
    Board::_underAttackX.clear();
    Board::_underAttackY.clear();

    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardSide[i][j] == _gd->_sideToMove) continue;
            if (Controller::askIfCanMove(Board::_activeTileX,Board::_activeTileY,i,j)) {
                Board::_underAttackX.push_back(i);
                Board::_underAttackY.push_back(j);
            }
        }
    }
}

void GameMenu::setFunc(const std::function<void(const std::string& message)> &dead) {
    _dead = dead;
}