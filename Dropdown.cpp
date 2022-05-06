//
// Created by laccs on 4/17/2022.
//

#include "Dropdown.hpp"

using namespace genv;

Dropdown::Dropdown(PrimeWindow *pw, int x, int y, int sx, int sy, std::vector<std::string> items, int visible)
        : Widget(pw,x,y,sx,sy), _items(std::move(items)), _visible(visible) {}

void Dropdown::draw() {
    //Box
    if (_focus) {
        gout << color(100,100,100);
    } else {
        gout << color(50,50,50);
    }
    gout << move_to(_x,_y) << box(_sx,_sy);

    //Text
    gout << color(0, 0, 0) << move_to(_x + _sx * (1 - _buttonWidth) / 2 - gout.twidth(_items[_selected]) / 2 + 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(_items[_selected]);
    gout << color(255, 255, 255) << move_to(_x + _sx * (1 - _buttonWidth) / 2 - gout.twidth(_items[_selected]) / 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text(_items[_selected]);

    //b = button
    int bx = _x + _sx * (1 - _buttonWidth);
    int bsx = _sx * _buttonWidth;

    gout << color(255,255,255) << move_to(bx,_y) << line(bsx,0) << move_to(bx,_y) << line(0,_sy);
    gout << color(0,0,0) << move_to(bx+bsx,_y+_sy) << line(-bsx,0) << move_to(bx+bsx,_y+_sy) << line(0,-_sy);

    gout << color(0, 0, 0) << move_to(bx + bsx / 2 - gout.twidth("v") / 2 + 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text("v");
    gout << color(255, 255, 255) << move_to(bx + bsx / 2 - gout.twidth("v") / 2,_y + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text("v");

    if (_isDown) {
        if (_visible >= (signed)_items.size()) {
            //i = item
            int iy = _y+_sy;

            for (int i=_front; i<_front+_visible; ++i) {
                gout << color(150,150,150) << move_to(_x,iy) << box(_sx,_sy);
                gout << color(0, 0, 0) << move_to(_x + _sx / 2 - gout.twidth(_items[i]) / 2 + 2,iy + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(_items[i]);
                gout << color(255, 255, 255) << move_to(_x + _sx / 2 - gout.twidth(_items[i]) / 2,iy + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text(_items[i]);

                iy += _sy;
            }
        } else {
            int iy = _y+_sy;

            for (int i=_front; i<_front+_visible; ++i) {
                gout << color(150,150,150) << move_to(_x,iy) << box(_sx,_sy);
                gout << color(0, 0, 0) << move_to(_x + _sx*(1-_buttonWidth) / 2 - gout.twidth(_items[i]) / 2 + 2,iy + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text(_items[i]);
                gout << color(255, 255, 255) << move_to(_x + _sx*(1-_buttonWidth) / 2 - gout.twidth(_items[i]) / 2,iy + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text(_items[i]);

                iy += _sy;
            }

            int sliderWhole = (_visible-2)*_sy;

            //Up button
            int by = _y + _sy;
            gout << color(255,255,255) << move_to(bx,by) << line(bsx,0) << move_to(bx,by) << line(0,_sy);
            gout << color(0,0,0) << move_to(bx+bsx,by+_sy) << line(-bsx,0) << move_to(bx+bsx,by+_sy) << line(0,-_sy);

            gout << color(0, 0, 0) << move_to(bx + bsx / 2 - gout.twidth("^") / 2 + 2,by + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text("^");
            gout << color(255, 255, 255) << move_to(bx + bsx / 2 - gout.twidth("^") / 2,by + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text("^");

            //Down button
            by += sliderWhole + _sy;
            gout << color(255,255,255) << move_to(bx,by) << line(bsx,0) << move_to(bx,by) << line(0,_sy);
            gout << color(0,0,0) << move_to(bx+bsx,by+_sy) << line(-bsx,0) << move_to(bx+bsx,by+_sy) << line(0,-_sy);

            gout << color(0, 0, 0) << move_to(bx + bsx / 2 - gout.twidth("v") / 2 + 2,by + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2 + 2) << text("v");
            gout << color(255, 255, 255) << move_to(bx + bsx / 2 - gout.twidth("v") / 2,by + _sy / 2 - (gout.cascent() + gout.cdescent()) / 2)<< text("v");

            //Slider
            float sliderStep = sliderWhole / (_items.size()-_visible+1);
            gout << color(100,100,100) << move_to(bx,_y+_sy+_sy+sliderStep*_front) << box(_sx*_buttonWidth,sliderStep);
        }
    }
}

void Dropdown::handle(const genv::event &ev) {
    if (ev.type == ev_mouse) {
        if (ev.button == btn_left) {

            if (ev.pos_x > _x + _sx * (1 - _buttonWidth) && ev.pos_x < _x + _sx * (1 - _buttonWidth) + _sx * _buttonWidth && ev.pos_y > _y && ev.pos_y < _y+_sy) {
                _isDown = !_isDown;
            }

            if (_isDown) {
                if (ev.pos_x > _x+_sx*(1-_buttonWidth) && ev.pos_x < _x+_sx && ev.pos_y > _y+_sy && ev.pos_y < _y+_sy+_sy && _front > 0) {
                    _front--;
                } else if (ev.pos_x > _x+_sx*(1-_buttonWidth) && ev.pos_x < _x+_sx && ev.pos_y > _y+_visible*_sy && ev.pos_y < _y+_visible*_sy+_sy && _front+_visible < (signed)_items.size()) {
                    _front++;
                }

                int iy = _y+_sy;
                for (int i=_front; i<_front+_visible; ++i) {
                    if (ev.pos_x > _x && ev.pos_x < _x+_sx*(1-_buttonWidth) && ev.pos_y > iy && ev.pos_y < iy+_sy) {
                        _selected = i;
                        setFocus(false);
                        break;
                    }
                    iy += _sy;
                }
            }

        } else if (ev.button == btn_wheelup && _front > 0) {
            _front--;
        } else if (ev.button == btn_wheeldown && (_front+_visible) < (signed)_items.size()) {
            _front++;
        }
    }
}

bool Dropdown::isFocus(const event &ev) const {
    if (_isDown) {
        return ev.pos_x > _x && ev.pos_x < _x + _sx && ev.pos_y > _y && ev.pos_y < _y + _sy*_visible && ev.type == genv::ev_mouse && ev.button == genv::btn_left;
    } else {
        return ev.pos_x > _x && ev.pos_x < _x + _sx && ev.pos_y > _y && ev.pos_y < _y + _sy && ev.type == genv::ev_mouse && ev.button == genv::btn_left;
    }
}

bool Dropdown::isFocusable() {
    return true;
}

void Dropdown::setFocus(bool focus) {
    _focus = focus;
    if (!_focus) _isDown = false;
}

std::string Dropdown::getItem() const {
    return _items[_selected];
}
