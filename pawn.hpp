#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.hpp"
class Pawn:public ChessPiece
{
public:
    Pawn(Couleur team,QGraphicsItem *parent = nullptr);
    void setImage();
    void moves();

 private:


};

#endif // PAWN_H
