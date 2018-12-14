#include "pion.hpp"
#include "game.hpp"
#include <QDebug>
#include <typeinfo>

extern Game * game;
Pion::Pion (Couleur team,QGraphicsItem *parent) : QGraphicsPixmapItem(parent), firstMove(true), side(team), isPlaced(true)
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));

}

void Pion::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == game->pieceToMove){
        game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        game->pieceToMove->decolor();
        game->pieceToMove = nullptr;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (game->getTurn() != this->getSide())&& (!game->pieceToMove)) )
        return;
    //selecting
    if(!game->pieceToMove){

        game->pieceToMove = this;
        game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
        game->pieceToMove->moves();
    }
    //Consuming counterPart of the boite
    else if(this->getSide() != game->pieceToMove->getSide()){
        this->getCurrentBoite()->mousePressEvent(event);
    }


}


void Pion::moves()
{
    location.clear();

    int row = this->getCurrentBoite()->rowLoc;

    int col = this->getCurrentBoite()->colLoc;
    if(this->getSide() == Couleur::Blanc)  {
        if(col > 0 && row > 0 && game->collection[(row-1)*12+col-1]->getPionCouleur() == Couleur::Noir) {
            location.append(game->collection[(row-1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && game->collection[(row-1)*12+col+1]->getPionCouleur() == Couleur::Noir) {
            location.append(game->collection[(row-1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!game->collection[(row-1)*12+col]->getHasPion())) {
            location.append(game->collection[(row-1)*12+col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[(row-2)*12+col]->getHasPion()){
                location.append(game->collection[(row-2)*12+col]);
                boxSetting(location.last());
            }
        }

    }
    else{
        if(col > 0 && row < 7 && game->collection[(row+1)*12+col-1]->getPionCouleur() == Couleur::Blanc) {//left
            location.append(game->collection[(row+1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row <  7 && game->collection[(row+1)*12+col+1]->getPionCouleur() == Couleur::Blanc) {//right
            location.append(game->collection[(row+1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row<7 && (!game->collection[(row+1)*12+col]->getHasPion())) {
            location.append(game->collection[(row+1)*12+col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[(row+2)*12+col]->getHasPion()){
                location.append(game->collection[(row+2)*12+col]);
                boxSetting(location.last());
            }

        }

    }

}

void Pion::setCurrentBoite(Boite *box)
{

    currentBox = box;
}

Boite * Pion::getCurrentBoite()
{
    return currentBox;
}

Couleur Pion::getSide()
{
    return side;
}

void Pion::setSide( Couleur value)
{
    side = value;
}

bool Pion::getIsPlaced()
{
    return isPlaced;
}

void Pion::setIsPlaced(bool value)
{
    isPlaced = value;

}
QList<Boite *> Pion::moveLocation()
{
    return location;
}
void Pion::decolor()
{
    for(size_t i = 0, n = location.size(); i < n;i++) {
         location[i]->resetOriginalColor();
    }
}

bool Pion::boxSetting(Boite *box)
{
    if(box->getHasPion()) {
        /*King *q = dynamic_cast<King*>(location.last()->currentPiece);
        if(q){
            box->setColor(Qt::blue);
        }
        else*/
            box->setCouleur(Qt::red);
        return true;
    }
    else
        location.last()->setCouleur(Qt::darkRed);
    return false;
}

