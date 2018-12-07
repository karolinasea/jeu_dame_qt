#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include <QGraphicsRectItem>
#include "chesspiece.hpp"
#include "game.hpp"
class Game;
class ChessBoard
{
public:
    ChessBoard(Game *g, int param);


    void drawBoxes(int x, int y);

    void setUpWhite();
    void setUpBlack();



    void addChessPiece();
    void reset();
private:
    Game *game;
    int param;
    QList <ChessPiece *> white;
    QList <ChessPiece *> black;



};

#endif // CHESSBOARD_H
