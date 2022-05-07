//
// Created by laccs on 3/31/2022.
//

#ifndef SAKK_TEXTBOX_HPP
#define SAKK_TEXTBOX_HPP

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
    Textbox(Menu* m, int x, int y, int sx, int sy);
    void draw() override;
    void handle(const genv::event& ev) override;
    bool isFocusable() override;

    const std::string &getString() const;
};


#endif //SAKK_TEXTBOX_HPP
