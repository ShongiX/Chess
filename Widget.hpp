//
// Created by laccs on 4/15/2022.
//

#ifndef SAKK_WIDGET_HPP
#define SAKK_WIDGET_HPP

#include "graphics.hpp"

class Menu;

class Widget {
protected:
    Menu* _m{};
    int _x{},_y{},_sx{},_sy{};
    bool _focus = false;
public:
    virtual void draw() = 0;
    virtual void handle(const genv::event& ev) {}
    Widget(Menu* m, int x, int y, int sx, int sy);
    Widget() = default;
    virtual bool isFocus(const genv::event& ev) const;
    virtual bool isFocusable() = 0;
    virtual void setFocus(bool focus);

    friend Menu;
};

struct Color {
    unsigned char r{},g{},b{};
    Color() = default;
    Color(int rr, int gg, int bb) : r(rr), g(gg), b(bb) {}
};

#endif //SAKK_WIDGET_HPP
