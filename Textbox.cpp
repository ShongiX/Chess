//
// Created by laccs on 3/31/2022.
//

#include <iostream>
#include "Textbox.hpp"

using namespace genv;

Textbox::Textbox(PrimeWindow* pw, int x, int y, int sx, int sy) : Widget(pw, x, y, sx, sy) {}

bool Textbox::isEmpty() {
    if (_string.empty()) return true;
    return false;
}

bool Textbox::isFull() {
    if (gout.twidth(_string + "A") > _sx) return true;
    return false;
}

void Textbox::addChar(const genv::event& ev) {
    _string.insert(_caretPos,ev.keyutf8);
    _caretPos++;
}

void Textbox::removeChar() {
    _string.erase(_string.begin()+_caretPos-1);
    _caretPos--;
}

void Textbox::deleteChar() {
    _string.erase(_string.begin()+_caretPos);
}

void Textbox::draw() {
    if (_focus) {
        gout << color(255,255,255) << move_to(_x,_y) << box(_sx,_sy);
        gout << color(100,100,100) << move_to(_x+1, _y+1) << box(_sx-2, _sy-2);
    } else {
        gout << color(100,100,100) << move_to(_x,_y) << box(_sx,_sy);
        gout << color(50,50,50) << move_to(_x+1, _y+1) << box(_sx-2, _sy-2);
    }

    int offset = 4;
    gout << color(0, 0, 0) << move_to(_x + 2 + offset,_y + _sy/2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(_string);
    gout << color(255, 255, 255) << move_to(_x + offset,_y + _sy/2 - (gout.cascent() + gout.cdescent()) / 2)<< text(_string);

    if (_focus) {
        std::string tmp = _string;
        int caretPos = _x + offset;
        for(int i = tmp.size(); i >= _caretPos; --i) tmp.erase(i);
        caretPos += gout.twidth(tmp);

        gout << color (255,255,255) << move_to(caretPos,_y) << line(0,_sy);
    }
}

void Textbox::handle(const genv::event& ev) {
    if (ev.keycode == key_backspace && !isEmpty() && _caretPos>0) {
        removeChar();
    } else if (ev.keycode == key_delete && (unsigned)_caretPos<_string.size()) {
        deleteChar();
    } else if (ev.keycode == key_left && _caretPos>0) {
        _caretPos--;
    } else if (ev.keycode == key_right && (unsigned)_caretPos<_string.size()) {
        _caretPos++;
    } else if (!isFull() && ( (ev.keycode >= 'a' && ev.keycode <= 'z') || (ev.keycode >= 'A' && ev.keycode <= 'Z') || (ev.keycode >= '0' && ev.keycode <= '9') )) {
        addChar(ev);
    }
}

bool Textbox::isFocusable() {
    return true;
}

const std::string &Textbox::getString() const {
    return _string;
}


