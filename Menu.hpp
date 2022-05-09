//
// Created by laccs on 3/13/2022.
//

#ifndef SAKK_MENU_H
#define SAKK_MENU_H

#include <vector>
#include "Widget.hpp"

class GameData;

class Menu {
protected:
    std::vector<Widget*> _widgets;

public:
    virtual void draw(int focus);
    virtual void handle(const genv::event& ev, int &focus);

    void addWidget(Widget *w);
    void resetFocus(int focus);
};

class GameMenu : public Menu {
    GameData* _gd{};
public:
    void handle(const genv::event& ev, int &focus) override;
    void build();
    void setInfo(GameData* gd);
};



#endif //SAKK_MENU_H
