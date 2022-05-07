//
// Created by laccs on 3/13/2022.
//

#include "Menu.hpp"
#include "Sprite.hpp"

using namespace genv;

void Menu::draw() {
    for (Widget* widget : _widgets) {
        widget->draw();
    }
}

void Menu::handle(const event& ev) {
    if (ev.type == ev_mouse) {
        for (Widget* widget : _widgets) {
            widget->handle(ev);
        }
    }
}

void Menu::addWidget(Widget *w) {
    _widgets.push_back(w);
}