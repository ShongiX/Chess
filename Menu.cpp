//
// Created by laccs on 3/13/2022.
//

#include "Menu.hpp"
#include "GameData.hpp"
#include "Piece.hpp"

using namespace genv;

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
    if (ev.type == ev_mouse) {
        int x = ev.pos_x / Board::TILE_SIZE;
        int y = ev.pos_y / Board::TILE_SIZE;


    }
}

void GameMenu::build() {
    Widget* tmp_board = _widgets.at(0);
    _widgets.clear();
    _widgets.push_back(tmp_board);

    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if (_gd->_boardSide[i][j] != EITHER) {
                new Piece(this,i*Board::TILE_SIZE,j*Board::TILE_SIZE,_gd->_boardType[i][j],_gd->_boardSide[i][j]);
            }
        }
    }
}

void GameMenu::setInfo(GameData* gd) {
    _gd = gd;
}
