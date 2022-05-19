//
// Created by laccs on 3/13/2022.
//

#ifndef SAKK_MENU_H
#define SAKK_MENU_H

#include <vector>
#include <functional>
#include "Widget.hpp"
#include "Enums.hpp"

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
    std::function<void(const std::string& message)> _dead = std::function<void(const std::string& message)>();

    void searchAttackedTiles();

public:
    void handle(const genv::event& ev, int &focus) override;
    void update();
    void build();
    void setInfo(GameData* gd);

    void setFunc(const std::function<void(const std::string& message)>& dead);
    void setFunc(const std::function<void(Side sideToMove)>& promote);

    std::function<void(Side sideToMove)> _promote = std::function<void(Side sideToMove)>();
    bool promotion = false;
};



#endif //SAKK_MENU_H
