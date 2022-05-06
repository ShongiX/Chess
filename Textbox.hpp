//
// Created by laccs on 3/31/2022.
//

#ifndef WIDGET_TEXTBOX_HPP
#define WIDGET_TEXTBOX_HPP

#include "Widget.hpp"

class Textbox : public Widget {
protected:
    std::string _string;
    int _first = 0;
    int _visible = 10;
    int _caretPos = 0;

    bool isEmpty();
    bool isFull();

    void addChar(const genv::event& ev);
    void removeChar();
    void deleteChar();

public:
    Textbox(PrimeWindow* pw, int x, int y, int sx, int sy);
    void draw() override;
    void handle(const genv::event& ev) override;
    bool isFocusable() override;

    const std::string &getString() const;
};


#endif //WIDGET_TEXTBOX_HPP
