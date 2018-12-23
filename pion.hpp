#ifndef PION_H
#define PION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "enumCouleur.hpp"
#include "boite.hpp"

class Boite;
class Pion : public QGraphicsPixmapItem
{
public:
    Pion(Couleur team, QGraphicsItem *parent = nullptr);

    void moves();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBoite(Boite *box);

    Boite *getCurrentBoite() ;

    Couleur getSide() ;
    void setSide( Couleur value);


    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <Boite *> movelocation();

    void decolor();

    bool boxSetting(Boite *box);

 private:
    Boite *currentBox;
    Couleur side;
    bool isPlaced;
    QList <Boite *> location;


};

#endif // PION_H
