//
// Created by laccs on 5/7/2022.
//

#include "Piece.hpp"
#include "GameData.hpp"
#include "Menu.hpp"

using namespace genv;

Board::Board(Menu *m, int x, int y, int sx, int sy) : Widget(m,x,y,sx,sy) {}

void Board::draw() {
    gout << color(181,136,99);
    for (int i = 0; i < GameData::BOARD_SIZE; ++i) {
        for (int j = 0; j < GameData::BOARD_SIZE; ++j) {
            if ((i+j)%2 != 0) {
                gout << move_to(i*TILE_SIZE,j*TILE_SIZE) << box(TILE_SIZE,TILE_SIZE);
            }
        }
    }
}

bool Board::isFocusable() {return false;}

Piece::Piece(Menu *m, int x, int y, Type type, Side side) : _type(type), _side(side) {
    _m = m;
    _x = x;
    _y = y;

    _m->addWidget(this);

    std::string fileName = "../resources/";
    if (_side == WHITE) {
        if (_type == 0) {fileName += "wQ.txt";}
        else if (_type == 1) {fileName += "wR.txt";}
        else if (_type == 2) {fileName += "wN.txt";}
        else if (_type == 3) {fileName += "wB.txt";}
        else if (_type == 4) {fileName += "wP.txt";}
        else {fileName += "wK.txt";}
    } else {
        if (_type == 0) {fileName += "bQ.txt";}
        else if (_type == 1) {fileName += "bR.txt";}
        else if (_type == 2) {fileName += "bN.txt";}
        else if (_type == 3) {fileName += "bB.txt";}
        else if (_type == 4) {fileName += "bP.txt";}
        else {fileName += "bK.txt";}
    }

    loadFromFile(fileName);
}

void Piece::handle(const genv::event &ev) {

}

bool Piece::isFocusable() {
    return true;
}
