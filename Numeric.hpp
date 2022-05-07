//
// Created by laccs on 4/16/2022.
//

#ifndef BEADANDO_NUMERIC_HPP
#define BEADANDO_NUMERIC_HPP

#include "Widget.hpp"

class Numeric : public Widget {
protected:
    int _value{};
    int _minLimit{},_maxLimit{};
    int _step = 1;
    float _buttonWidth = 0.2; //Button size relative to whole widget
public:
    Numeric(Menu* m,int x, int y, int sx, int sy,int minLimit, int maxLimit);
    void draw() override;
    void handle(const genv::event& ev) override;
    bool isFocusable() override;

    int getValue() const;
};


#endif //BEADANDO_NUMERIC_HPP
