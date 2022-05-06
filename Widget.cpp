//
// Created by laccs on 4/15/2022.
//

#include "Widget.hpp"
#include "PrimeWindow.hpp"

Widget::Widget(PrimeWindow* pw, int x, int y, int sx, int sy) : _pw(pw), _x(x), _y(y), _sx(sx), _sy(sy){
    _pw->addWidget(this);
}

bool Widget::isFocus(const genv::event &ev) const {
        return ev.pos_x > _x && ev.pos_x < _x + _sx && ev.pos_y > _y && ev.pos_y < _y + _sy && ev.type == genv::ev_mouse && ev.button == genv::btn_left;
}

void Widget::setFocus(bool focus) {
    _focus = focus;
}
