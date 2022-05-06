//
// Created by laccs on 4/7/2022.
//

#ifndef WIDGET_BUTTON_HPP
#define WIDGET_BUTTON_HPP

#include "Widget.hpp"
#include <functional>

class PrimeWindow;

enum ButtonState {NEUTRAL, HOVER, CLICKED};

class Button : public Widget {
    std::string _name;
    std::function<void()> _func = std::function<void()>();
    ButtonState _state = NEUTRAL;
public:
    Button(PrimeWindow* pw,int x, int y, int sx, int sy, std::string name,std::function<void()> func);

    void handle(const genv::event& ev) override;
    void draw() override;
    bool isFocusable() override;
    bool isFocus(const genv::event &ev) const override;

    const std::string &getName() const;

    bool pressed = false;
};


#endif //WIDGET_BUTTON_HPP
