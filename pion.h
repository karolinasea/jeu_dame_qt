#ifndef PION_H
#define PION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "enumCouleur.h"
//#include "listecoups.h"
#include "generateur.h"
class generateur;
class Boite;
class Pion : public QGraphicsPixmapItem
{
public:
    Pion(Couleur team, QGraphicsItem *parent = nullptr);

    void moves();
    void conversionDame();

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCurrentBoite(Boite *box);

    Boite *getCurrentBoite() ;
    QList <Boite *> boitePionEnnemi;
    QList <Boite *> location;

    Couleur getSide() ;
    void setSide( Couleur value);


    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <Boite *> getLocation();
    QList <Boite *> getEnnemis();
    void decolor();

    bool boxSetting(Boite *box);
    generateur *gene;
    bool isDame;

 private:
    Boite *currentBox;
    Couleur side;
    bool isPlaced;

    //QList <Boite *> boitePionEnnemi;
    //QList <Boite *> location;
};

#endif // PION_H
