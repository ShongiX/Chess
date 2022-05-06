//
// Created by laccs on 4/16/2022.
//

#include "Numeric.hpp"

using namespace genv;

Numeric::Numeric(PrimeWindow *pw, int x, int y, int sx, int sy, int minLimit, int maxLimit) : Widget(pw,x,y,sx,sy), _minLimit(minLimit), _maxLimit(maxLimit) {
    _value = _minLimit;
}

void Numeric::draw() {
    //Box
    if (_focus) {
        gout << color(100,100,100);
    } else {
        gout << color(50,50,50);
    }
    gout << move_to(_x,_y) << box(_sx,_sy);

    //Text
    gout << color(0, 0, 0) << move_to(_x + _sx * (1 - _buttonWidth) / 2 - gout.twidth(std::to_string(_value)) / 2 + 2, _y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(std::to_string(_value));
    gout << color(255, 255, 255) << move_to(_x + _sx * (1 - _buttonWidth) / 2 - gout.twidth(std::to_string(_value)) / 2, _y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2) << text(std::to_string(_value));

    //b = button
    int bx = _x + _sx * (1 - _buttonWidth);
    int by = _y;
    int bsx = _sx * _buttonWidth;
    int bsy = _sy/2;

    //Increment button
    gout << color(255,255,255) << move_to(bx,by) << line(bsx,0) << move_to(bx,by) << line(0,bsy);
    gout << color(0,0,0) << move_to(bx+bsx,by+bsy) << line(-bsx,0) << move_to(bx+bsx,by+bsy) << line(0,-bsy);

    gout << color(0, 0, 0) << move_to(bx + bsx / 2 - gout.twidth("+") / 2 + 2,by + bsy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text("+");
    gout << color(255, 255, 255) << move_to(bx + bsx / 2 - gout.twidth("+") / 2,by + bsy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text("+");

    by += bsy;

    //Decrement button
    gout << color(255,255,255) << move_to(bx,by) << line(bsx,0) << move_to(bx,by) << line(0,bsy);
    gout << color(0,0,0) << move_to(bx+bsx,by+bsy) << line(-bsx,0) << move_to(bx+bsx,by+bsy) << line(0,-bsy);

    gout << color(0, 0, 0) << move_to(bx + bsx / 2 - gout.twidth("-") / 2 + 2,by + bsy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text("-");
    gout << color(255, 255, 255) << move_to(bx + bsx / 2 - gout.twidth("-") / 2,by + bsy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text("-");
}

void Numeric::handle(const genv::event &ev) {
    if (ev.type == ev_key) {
        if (ev.keycode == key_up && _value < _maxLimit) {
            _value += _step;
        } else if (ev.keycode == key_down && _value > _minLimit) {
            _value -= _step;
        } else if (ev.keycode == key_pgup && _value+10*_step <= _maxLimit) {
            _value += 10*_step;
        } else if (ev.keycode == key_pgdn && _value-10*_step >= _minLimit) {
            _value -= 10*_step;
        }
    } else if (ev.type == ev_mouse) {
        int bx = _x + _sx * (1 - _buttonWidth);
        int by = _y;
        int bsx = _sx * _buttonWidth;
        int bsy = _sy/2;

        if (ev.pos_x > bx && ev.pos_x < bx+bsx && ev.pos_y > by && ev.pos_y < by+bsy && ev.button == btn_left && _value < _maxLimit) {
            _value += _step;
        }

        by += bsy;

        if (ev.pos_x > bx && ev.pos_x < bx+bsx && ev.pos_y > by && ev.pos_y < by+bsy && ev.button == btn_left && _value > _minLimit) {
            _value -= _step;
        }
    }

}

bool Numeric::isFocusable() {
    return true;
}

int Numeric::getValue() const {
    return _value;
}
