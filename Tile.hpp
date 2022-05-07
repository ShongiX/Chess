//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_TILE_HPP
#define SAKK_TILE_HPP


class Piece;
class Game;

class Tile {
    bool isFree = true;
    Piece* piece{};

    friend Game;
};


#endif //SAKK_TILE_HPP
