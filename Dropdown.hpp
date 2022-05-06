//
// Created by laccs on 4/17/2022.
//

#ifndef BEADANDO_DROPDOWN_HPP
#define BEADANDO_DROPDOWN_HPP

#include "Widget.hpp"
#include <vector>

class Dropdown : public Widget {
protected:
    std::vector<std::string> _items;
    int _front = 0; //index of first visible item
    int _visible; //number of visible items, >= 3
    int _selected = 0; //index of selected item
    bool _isDown = false; //is the list dropped down
    float _buttonWidth = 0.2;
public:
    Dropdown(PrimeWindow* pw, int x, int y, int sx, int sy, std::vector<std::string> items, int visible);
    void draw() override;
    void handle(const genv::event& ev) override;
    bool isFocus(const genv::event& ev) const override;
    bool isFocusable() override;
    void setFocus(bool focus) override;

    std::string getItem() const;
};


#endif //BEADANDO_DROPDOWN_HPP
