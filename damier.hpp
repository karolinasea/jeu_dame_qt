#ifndef DAMIER_H
#define DAMIER_H

#include <QGraphicsRectItem>
//#include "pion.hpp"

#include "generateur.hpp"
#include "game.hpp"
class Game;
class Damier
{
public:
    Damier(Game *g, int param);


    void drawBoites(int x, int y);

    void setUpWhite();
    void setUpBlack();



    void addPion();
    void reset();
private:    
    Game *game;
    int param;
    QList <Pion *> white;
    QList <Pion *> black;




};

#endif // DAMIER_H
