//
// Created by laccs on 4/7/2022.
//

#include "Button.hpp"
#include "PrimeWindow.hpp"

using namespace genv;

Button::Button(PrimeWindow* pw,int _x, int _y, int _sx, int sy, std::string name, std::function<void()> func) : Widget(pw,_x,_y,_sx,sy) {
    _name = std::move(name);
    _func = func;
}

void Button::handle(const genv::event& ev) {
    if (ev.button == btn_left) {
        pressed = true;
    } else if (ev.button == -btn_left) {
        pressed = false;
    }

    _func();
}

void Button::draw() {
    //Box
    gout << color(100,100,100) << move_to(_x,_y) << box(_sx,_sy);
    //Shadow
    gout << color(0,0,0) << move_to(_x+_sx/2- gout.twidth(_name)/2,_y+_sy/2-( gout.cascent()+ gout.cdescent())/2) << move(2,2) << genv::text(_name);
    //_name
    gout << color(255,255,255) << move_to(_x+_sx/2- gout.twidth(_name)/2,_y+_sy/2-( gout.cascent()+ gout.cdescent())/2) << genv::text(_name);
    //Outline
    gout << color(255,255,255) << move_to(_x,_y) << line(_sx,0) << move_to(_x,_y) << line(0,_sy);
    gout << color(0,0,0) << move_to(_x+_sx,_y+_sy) << line(-_sx,0) << move_to(_x+_sx,_y+_sy) << line(0,-_sy);
}

bool Button::isFocusable() {
    return true;
}

bool Button::isFocus(const genv::event &ev) const {
    return ev.type == genv::ev_mouse && ev.pos_x > _x && ev.pos_x < _x + _sx && ev.pos_y > _y && ev.pos_y < _y + _sy;
}

const std::string &Button::getName() const {
    return _name;
}


