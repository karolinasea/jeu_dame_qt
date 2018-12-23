#include "pion.hpp"
#include "game.hpp"
#include <QDebug>
#include <typeinfo>


Pion::Pion (Couleur team,QGraphicsItem *parent) : QGraphicsPixmapItem(parent), side(team), isPlaced(true)
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));

}

void Pion::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //Deselect
    if(this == currentBox->game->pieceToMove){
        currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        currentBox->game->pieceToMove->decolor();
        currentBox->game->pieceToMove = nullptr;
       return;
    }
    //if it is already consumed or not the respective color's turn
    if((!getIsPlaced() )|| ( (currentBox->game->getTurn() != this->getSide())&& (!currentBox->game->pieceToMove)) )
        return;
    //selecting
    if(!currentBox->game->pieceToMove){

        currentBox->game->pieceToMove = this;
        currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
        currentBox->game->pieceToMove->moves();
    }
    //Consuming counterPart of the boite
    else if(this->getSide() != currentBox->game->pieceToMove->getSide()){
        this->getCurrentBoite()->mousePressEvent(event);
    }


}


void Pion::moves()
{
    location.clear();

    int row = this->getCurrentBoite()->rowLoc;

    int col = this->getCurrentBoite()->colLoc;
    if(this->getSide() == Couleur::Blanc)  {
        if(col > 0 && row > 0 && currentBox->game->tab_damier[(row-1)*12+col-1]->getPionCouleur() == Couleur::Noir) {  //gauche
            location.append(currentBox->game->tab_damier[(row-1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < currentBox->game->nbCases-1 && row > 0 && currentBox->game->tab_damier[(row-1)*12+col+1]->getPionCouleur() == Couleur::Noir) { //droite
            location.append(currentBox->game->tab_damier[(row-1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!currentBox->game->tab_damier[(row-1)*12+col]->getHasPion())) {
            location.append(currentBox->game->tab_damier[(row-1)*12+col]);
            boxSetting(location.last());

        }

    }
    else{
        if(col > 0 && row < currentBox->game->nbCases-1 && currentBox->game->tab_damier[(row+1)*12+col-1]->getPionCouleur() == Couleur::Blanc) {//left
            location.append(currentBox->game->tab_damier[(row+1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < currentBox->game->nbCases-1 && row <  currentBox->game->nbCases-1 && currentBox->game->tab_damier[(row+1)*12+col+1]->getPionCouleur() == Couleur::Blanc) {//right
            location.append(currentBox->game->tab_damier[(row+1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row< currentBox->game->nbCases-1 && (!currentBox->game->tab_damier[(row+1)*12+col]->getHasPion())) {
            location.append(currentBox->game->tab_damier[(row+1)*12+col]);
            boxSetting(location.last());


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
QList<Boite *> Pion::movelocation()
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
        /*King *q = dynamic_cast<King*>(tab_damier.last()->currentPiece);
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

