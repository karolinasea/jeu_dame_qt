#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

#include "boite.hpp"

class boite;
class ChessPiece:public QGraphicsPixmapItem
{
public:
    ChessPiece(Couleur team = Couleur::None,QGraphicsItem *parent = nullptr);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBox(boite *box);

    boite *getCurrentBox() ;

    Couleur getSide() ;
    void setSide( Couleur value);
    virtual void setImage() = 0;

    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <boite *> moveLocation();
    virtual void moves() = 0;
    void decolor();

    bool firstMove;

    bool boxSetting(boite *box);
protected:
    boite *currentBox;
    Couleur side;
    bool isPlaced;
    QList <boite *> location;


};

#endif // CHESSPIECE_H
