//
// Created by laccs on 4/15/2022.
//

#ifndef SDL_WIDGET_HPP
#define SDL_WIDGET_HPP

#include "graphics.hpp"

class PrimeWindow;

class Widget {
protected:
    PrimeWindow* _pw{};
    int _x{},_y{},_sx{},_sy{};
    bool _focus = false;
public:
    virtual void draw() = 0;
    virtual void handle(const genv::event& ev) {}
    Widget(PrimeWindow* pw, int x, int y, int sx, int sy);
    Widget() = default;
    virtual bool isFocus(const genv::event& ev) const;
    virtual bool isFocusable() = 0;
    virtual void setFocus(bool focus);
};


#endif //SDL_WIDGET_HPP
