//
// Created by laccs on 4/7/2022.
//

#ifndef SAKK_BUTTON_HPP
#define SAKK_BUTTON_HPP

#include "Widget.hpp"
#include <functional>

enum class ButtonState {NEUTRAL, HOVER, CLICKED};

class Button : public Widget {
    std::string _name;
    std::function<void()> _func = std::function<void()>();
    ButtonState _state = ButtonState::NEUTRAL;
public:
    Button(Menu* m,int x, int y, int sx, int sy, std::string name,std::function<void()> func);

    void handle(const genv::event& ev) override;
    void draw() override;
    bool isFocusable() override;
    bool isFocus(const genv::event &ev) const override;

    const std::string &getName() const;

    bool pressed = false;
};


#endif //SAKK_BUTTON_HPP
