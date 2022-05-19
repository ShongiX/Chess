//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_BOARD_HPP
#define SAKK_BOARD_HPP

#include "Sprite.hpp"
#include "Enums.hpp"
#include "Widget.hpp"

class Board : public Widget {
public:
    static int _activeTileX;
    static int _activeTileY;

    static std::vector<int> _underAttackX;
    static std::vector<int> _underAttackY;

    static const int TILE_SIZE = 100;

    Board(Menu* m,int x, int y, int sx, int sy);
    void draw() override;
    bool isFocusable() override;
};

#endif //SAKK_BOARD_HPP
