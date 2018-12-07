#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "chessbox.hpp"

class ChessBox;
class ChessPiece:public QGraphicsPixmapItem
{
public:
    ChessPiece(Couleur team = Couleur::None,QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(ChessBox *box);

    ChessBox *getCurrentBox() ;

    Couleur getSide() ;
    void setSide( Couleur value);
    virtual void setImage() = 0;

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <ChessBox *> moveLocation();
    virtual void moves() = 0;
    void decolor();

    bool firstMove;

    bool boxSetting(ChessBox *box);
protected:
    ChessBox *currentBox;
    Couleur side;
    bool isPlaced;
    QList <ChessBox *> location;


};

#endif // CHESSPIECE_H
