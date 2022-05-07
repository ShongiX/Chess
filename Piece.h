//
// Created by laccs on 5/7/2022.
//

#ifndef SAKK_PIECE_H
#define SAKK_PIECE_H

enum class Side {WHITE, BLACK};

class Piece {
protected:
    Side _side;

public:
    Piece(Side side);
    virtual bool canMove(int x, int y) = 0;
};

class Queen : public Piece {
public:
    Queen(Side side);
    bool canMove(int x, int y) override;
};

class Rook : public Piece {
public:
    Rook(Side side);
    bool canMove(int x, int y) override;
};

class Knight : public Piece {
public:
    Knight(Side side);
    bool canMove(int x, int y) override;
};

class Bishop : public Piece {
public:
    Bishop(Side side);
    bool canMove(int x, int y) override;
};

class Pawn : public Piece {
public:
    Pawn(Side side);
    bool canMove(int x, int y) override;
};

class King : public Piece {
public:
    King(Side side);
    bool canMove(int x, int y) override;
};


#endif //SAKK_PIECE_H
