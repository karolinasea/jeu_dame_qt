#ifndef PION_H
#define PION_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>
#include "enumCouleur.hpp"
//#include "listecoups.hpp"
#include "generateur.hpp"
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

    Couleur getSide() ;
    void setSide( Couleur value);


    bool getIsPlaced() ;
    void setIsPlaced(bool value);

    QList <Boite *> getLocation();
    QList <Boite *> getEnnemis();
    void decolor();

    bool boxSetting(Boite *box);
generateur *gene;
 private:
    Boite *currentBox;
    Couleur side;
    bool isPlaced;
    bool isDame;
    QList <Boite *> boitePionEnnemi;
    QList <Boite *> location;



};

#endif // PION_H
