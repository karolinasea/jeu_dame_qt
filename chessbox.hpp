#ifndef CHESSBOX_H
#define CHESSBOX_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>

#include "enumCouleur.hpp"
#include "chesspiece.hpp"


class ChessPiece;
class ChessBox:public QGraphicsRectItem
{
public:

    //Constructor
    ChessBox(int taille, QGraphicsItem *parent=nullptr);
    ~ChessBox();


    //public member function
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(ChessPiece *piece);


    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = nullptr);

    void checkForCheck();

    Couleur getChessPieceColor() ;
    void setChessPieceColor(Couleur value);

    char rowLoc;
    char colLoc;

    ChessPiece * currentPiece;

private:
    int taille;
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    Couleur chessPieceColor;


};

#endif // CHESSBOX_H
