//
// Created by laccs on 5/7/2022.
//

#include "Board.hpp"
#include "GameData.hpp"
#include "Menu.hpp"

using namespace genv;

int Board::_activeTileX = -1;
int Board::_activeTileY = -1;

Board::Board(Menu *m, int x, int y, int sx, int sy) : Widget(m,x,y,sx,sy) {}

void Board::draw() {

    //Tiles
    gout << color(181,136,99);
    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if ((i+j)%2 != 0) {
                gout << move_to(i*TILE_SIZE,j*TILE_SIZE) << box(TILE_SIZE,TILE_SIZE);
            }
        }
    }

    if (_activeTileX != -1) {
        //Selected piece
        Color backgroundC;
        if ((_x/_sx + _y/_sy )%2 == 0) backgroundC = Color(240,217,181);
        else backgroundC = Color(181,136,99);

        Color tileC(255,255,0);
        tileC = tileC.opacity(backgroundC,0.4);

        gout << move_to(_activeTileX*TILE_SIZE,_activeTileY*TILE_SIZE) << color(tileC.r,tileC.g,tileC.b) << box(TILE_SIZE,TILE_SIZE);

        //Attacked tiles
        for (unsigned i = 0; i < _underAttackX.size(); ++i) {
            if ((_underAttackX[i]+_underAttackY[i])%2 == 0) backgroundC = Color(240,217,181);
            else backgroundC = Color(181,136,99);

            Color attackedC(255,0,0);
            attackedC = attackedC.opacity(backgroundC,0.4);

            gout << move_to(_underAttackX[i]*TILE_SIZE,_underAttackY[i]*TILE_SIZE) << color(attackedC.r,attackedC.g,attackedC.b) << box(TILE_SIZE,TILE_SIZE);
        }
    }
}

bool Board::isFocusable() {return false;}
