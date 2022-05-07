//
// Created by laccs on 3/31/2022.
//

#include "Text.hpp"

using namespace genv;

Text::Text(Menu* m,int x, int y, int sx, int sy, const std::string& str) : Widget(m,x,y,sx,sy) {
    _string = str;
}

void Text::draw() {
    //Background for debugging purposes
    //gout << color(100,100,100) << move_to(_x,_y) << box(_sx,_sy);
    gout << color(0, 0, 0) << move_to(_x + _sx / 2 - gout.twidth(_string) / 2 + 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(_string);
    gout << color(255, 255, 255) << move_to(_x + _sx / 2 - gout.twidth(_string) / 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text(_string);
}

void Text::handle(const genv::event& ev) {}

bool Text::isFocusable() {
    return false;
}


const std::string &Text::getString() const {
    return _string;
}