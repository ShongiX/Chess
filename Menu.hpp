//
// Created by laccs on 3/13/2022.
//

#ifndef SAKK_MENU_H
#define SAKK_MENU_H

#include "Sprite.hpp"

class Menu {
protected:
    std::vector<Widget*> _widgets;

public:
    virtual void draw();
    virtual void handle(const genv::event& ev);

    void addWidget(Widget *w);
};



#endif //SAKK_MENU_H
