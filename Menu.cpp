//
// Created by laccs on 3/13/2022.
//

#include <iostream>
#include "Menu.hpp"

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

void GameMenu::setInfo(GameData* gd) {
    _gd = gd;
}