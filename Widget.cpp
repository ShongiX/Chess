//
// Created by laccs on 4/15/2022.
//

#include "Widget.hpp"
#include "Menu.hpp"

Widget::Widget(Menu* m, int x, int y, int sx, int sy) : _m(m), _x(x), _y(y), _sx(sx), _sy(sy){
    _m->addWidget(this);
}

bool Widget::isFocus(const genv::event &ev) const {
        return ev.pos_x > _x && ev.pos_x < _x + _sx && ev.pos_y > _y && ev.pos_y < _y + _sy && ev.type == genv::ev_mouse && ev.button == genv::btn_left;
}

void Widget::setFocus(bool focus) {
    _focus = focus;
}

Color Color::opacity(Color background, float alpha) {
    return Color(
            (1-alpha) * background.r + alpha * r,
            (1-alpha) * background.g + alpha * g,
            (1-alpha) * background.b + alpha * b
    );
}

void Box::draw() {
    genv::gout << genv::move_to(_x,_y) << genv::color(150,150,150) << genv::box(_sx,_sy);
}

Box::Box(Menu* m, int x, int y, int sx, int sy) : Widget(m,x,y,sx,sy) {}
