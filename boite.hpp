#ifndef BOITE_H
#define BOITE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>


#include "enumCouleur.hpp"
#include "pion.hpp"


class Pion;
class Game;
class Boite:public QGraphicsRectItem
{
public:

    //Constructor
    Boite(Game *g, QGraphicsItem *parent=nullptr);
    ~Boite();


    //public member function
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setCouleur(QColor couleur);
    void placePiece(Pion *piece);


    void resetOriginalColor();
    void setOriginalColor(QColor couleur);

    bool getHasPion();
    void setHasPion(bool value, Pion *piece = nullptr);

    void checkForCheck();

    Couleur getPionCouleur() ;
    void setPionCouleur(Couleur couleur);

    char rowLoc;
    char colLoc;

    Pion * currentPiece;

    Game *game;  //public pour pion

private:    

    QBrush brush;
    QColor couleurDorigine;
    bool hasPion;
    Couleur couleurPion;


};

#endif // BOITE_H
