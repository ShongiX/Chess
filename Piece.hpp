//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_PIECE_HPP
#define SAKK_PIECE_HPP

#include "Sprite.hpp"
#include "Enums.hpp"
#include "Widget.hpp"

class Board : public Widget {
public:
    Board(Menu* m,int x, int y, int sx, int sy);
    void draw() override;
    bool isFocusable() override;

    static const int TILE_SIZE = 100;
};

class Piece : public Sprite {
protected:
    Type _type;
    Side _side;

public:
    Piece(Menu* m,int x, int y, Type type, Side side);
    void handle(const genv::event& ev) override;
    bool isFocusable() override;
};


#endif //SAKK_PIECE_HPP
