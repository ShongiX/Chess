//
// Created by laccs on 5/7/2022.
//

#include "Piece.h"

Piece::Piece(Side side) : _side(side) {}

Queen::Queen(Side side) : Piece(side) {}

bool Queen::canMove(int x, int y) {
    return false;
}

Rook::Rook(Side side) : Piece(side) {}

bool Rook::canMove(int x, int y) {
    return false;
}

Knight::Knight(Side side) : Piece(side) {}

bool Knight::canMove(int x, int y) {
    return false;
}

Bishop::Bishop(Side side) : Piece(side) {}

bool Bishop::canMove(int x, int y) {
    return false;
}

Pawn::Pawn(Side side) : Piece(side) {}

bool Pawn::canMove(int x, int y) {
    return false;
}

King::King(Side side) : Piece(side) {}

bool King::canMove(int x, int y) {
    return false;
}
