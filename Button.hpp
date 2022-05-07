//
// Created by laccs on 4/7/2022.
//

#ifndef SAKK_BUTTON_HPP
#define SAKK_BUTTON_HPP

#include "Widget.hpp"
#include <functional>

class Button : public Widget {
    std::string _name;
    std::function<void()> _func = std::function<void()>();
public:
    Button(Menu* m,int x, int y, int sx, int sy, std::string name,std::function<void()> func);

    void handle(const genv::event& ev) override;
    void draw() override;
    bool isFocusable() override;
    bool isFocus(const genv::event &ev) const override;

    const std::string &getName() const;

    bool pressed = false;
    bool released = false;
};


#endif //SAKK_BUTTON_HPP
