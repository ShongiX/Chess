//
// Created by laccs on 5/7/2022.
//

#include "Game.hpp"
#include "Piece.h"

Game::Game() {
    _gd = new GameData();

    for (int i = 0; i < BOARD_SIZE; ++i) {
        std::vector<Tile> line;
        for (int j = 0; j < BOARD_SIZE; ++j) {
            line.emplace_back();
        }
        _gd->_board.push_back(line);
    }

    int i = 0;
    _gd->_board[i][0].piece = new Rook(Side::BLACK);
    _gd->_board[i][1].piece = new Knight(Side::BLACK);
    _gd->_board[i][2].piece = new Bishop(Side::BLACK);
    _gd->_board[i][3].piece = new Queen(Side::BLACK);
    _gd->_board[i][4].piece = new King(Side::BLACK);
    _gd->_board[i][5].piece = new Bishop(Side::BLACK);
    _gd->_board[i][6].piece = new Knight(Side::BLACK);
    _gd->_board[i][7].piece = new Rook(Side::BLACK);

    i = 1;
    _gd->_board[i][0].piece = new Pawn(Side::BLACK);
    _gd->_board[i][1].piece = new Pawn(Side::BLACK);
    _gd->_board[i][2].piece = new Pawn(Side::BLACK);
    _gd->_board[i][3].piece = new Pawn(Side::BLACK);
    _gd->_board[i][4].piece = new Pawn(Side::BLACK);
    _gd->_board[i][5].piece = new Pawn(Side::BLACK);
    _gd->_board[i][6].piece = new Pawn(Side::BLACK);
    _gd->_board[i][7].piece = new Pawn(Side::BLACK);

    i = 6;
    _gd->_board[i][0].piece = new Pawn(Side::WHITE);
    _gd->_board[i][1].piece = new Pawn(Side::WHITE);
    _gd->_board[i][2].piece = new Pawn(Side::WHITE);
    _gd->_board[i][3].piece = new Pawn(Side::WHITE);
    _gd->_board[i][4].piece = new Pawn(Side::WHITE);
    _gd->_board[i][5].piece = new Pawn(Side::WHITE);
    _gd->_board[i][6].piece = new Pawn(Side::WHITE);
    _gd->_board[i][7].piece = new Pawn(Side::WHITE);

    i = 7;
    _gd->_board[i][0].piece = new Rook(Side::WHITE);
    _gd->_board[i][1].piece = new Knight(Side::WHITE);
    _gd->_board[i][2].piece = new Bishop(Side::WHITE);
    _gd->_board[i][3].piece = new Queen(Side::WHITE);
    _gd->_board[i][4].piece = new King(Side::WHITE);
    _gd->_board[i][5].piece = new Bishop(Side::WHITE);
    _gd->_board[i][6].piece = new Knight(Side::WHITE);
    _gd->_board[i][7].piece = new Rook(Side::WHITE);
}
