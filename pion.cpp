#include "pion.hpp"
#include "game.hpp"
#include <QDebug>
#include <typeinfo>


Pion::Pion (Couleur team,QGraphicsItem *parent) : QGraphicsPixmapItem(parent), side(team), isPlaced(true), isDame(false)
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));

}

void Pion::conversionDame ()
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap(":/images/dame_blanche.png"));
    else
        setPixmap(QPixmap(":/images/dame_noire.png"));

}

void Pion::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //si deja mangee ou pas le tour de la couleur
    if((!getIsPlaced() )|| ( (currentBox->game->getTurn() != this->getSide())&& (!currentBox->game->pieceToMove)) )
        return;

    //Deselect
    if(this == currentBox->game->pieceToMove){
        currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        currentBox->game->pieceToMove->decolor();
        currentBox->game->pieceToMove = nullptr;
       return;
    }

    //selecting
    if(!currentBox->game->pieceToMove){

        currentBox->game->pieceToMove = this;
        currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
        currentBox->game->pieceToMove->moves();
    }
    //Consuming counterPart of the boite   UTILITé ??
    /*else if(this->getSide() != currentBox->game->pieceToMove->getSide()){
        qDebug()<<"oui ";
        this->getCurrentBoite()->mousePressEvent(event);
    }*/


}


void Pion::moves()
{
    location.clear(); 
    boitePionEnnemi.clear(); 

    int row = this->getCurrentBoite()->rowLoc; //get the row number of the box on which the pawn is placed
    char taille = currentBox->game->nbCases; //nbCases is the size of the board (8x8 or 10x10..)
    int col = this->getCurrentBoite()->colLoc; //get the column number of the box on which the pawn is placed
    
    gene = new generateur(taille, row, col, currentBox->game->tab_damier, this->getSide());
    gene->remplirListes();

    //return ;

    if(this->getSide() == Couleur::Blanc)
    {
        if(col > 1 && row > 1 && currentBox->game->tab_damier[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
        {  
            // qqch a manger a gauche ?
            if(!currentBox->game->tab_damier[(row-2)*taille+col-2]->getHasPion())
            { 
                // on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row-2)*taille+col-2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row-1)*taille+col-1]);
                //boxSetting(location.last());
            }
        }
        if(col < taille-2 && row > 1 && currentBox->game->tab_damier[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
        { 
            //qqch a manger a droite ?
            if(!currentBox->game->tab_damier[(row-2)*taille+col+2]->getHasPion())
            { 
                // on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row-2)*taille+col+2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row-1)*taille+col+1]);
                //boxSetting(location.last());
            }
        }

        if(col > 1 && row < taille-2 && currentBox->game->tab_damier[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
        {  
            //qqch a manger a gauche arriere ?
            if(!currentBox->game->tab_damier[(row+2)*taille+col-2]->getHasPion())
            { 
                // on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row+2)*taille+col-2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row+1)*taille+col-1]);
                //boxSetting(location.last());
            }
        }
        if(col <taille-2 && row < taille-2 && currentBox->game->tab_damier[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
        {  
            // qqch a manger a droite arriere ?
            if(!currentBox->game->tab_damier[(row+2)*taille+col+2]->getHasPion())
            { 
                // on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row+2)*taille+col+2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row+1)*taille+col+1]);
                //boxSetting(location.last());
            }
        }

        //si le pion ne peut manger aucun pion on regarde s'il peut avancer a droite ou a gauche
        if(location.size()==0 && boitePionEnnemi.size()==0)
        {
            //checks that row and col are in the board and not bigger and if case avt droite n'as pas de pion
            if(row > 0 && col < taille-1 && (!currentBox->game->tab_damier[(row-1)*taille+col+1]->getHasPion()))
            { 
                //droite
                location.append(currentBox->game->tab_damier[(row-1)*taille+col+1]);
                boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());

            }
            if(col > 0 && row > 0 && (!currentBox->game->tab_damier[(row-1)*taille+col-1]->getHasPion()))
            { 
                //gauche
                location.append(currentBox->game->tab_damier[(row-1)*taille+col-1]);
                boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());
            }
        }

    }
    else //pour les pions noirs
    {
        if(col > 1 && row < taille-2 && currentBox->game->tab_damier[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
        {
            //qqch a manger a gauche ?
            if(!currentBox->game->tab_damier[(row+2)*taille+col-2]->getHasPion())
            { 
                //on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row+2)*taille+col-2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row+1)*taille+col-1]);
                //boxSetting(location.last());
            }
        }
        if(col <taille-2 && row < taille-2 && currentBox->game->tab_damier[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            //qqch a manger a droite ?
            if(!currentBox->game->tab_damier[(row+2)*taille+col+2]->getHasPion())
            { 
                //on verifie ya pas de pion sur point de chute
                boitePionEnnemi.append(currentBox->game->tab_damier[(row+1)*taille+col+1]);
                location.append(currentBox->game->tab_damier[(row+2)*taille+col+2]);
                //boxSetting(location.last());
            }
        }
        if(col > 1 && row >1 && currentBox->game->tab_damier[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
        {
            //qqch a manger a gauche arriere ?
            if(!currentBox->game->tab_damier[(row-2)*taille+col-2]->getHasPion())
            { 
                //on verifie ya pas de pion sur point de chute
                location.append(currentBox->game->tab_damier[(row-2)*taille+col-2]);
                boitePionEnnemi.append(currentBox->game->tab_damier[(row-1)*taille+col-1]);
                //boxSetting(location.last());
            }
        }
        if(col <taille-2 && row >1 && currentBox->game->tab_damier[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            //qqch a manger a droite arriere ?
            if(!currentBox->game->tab_damier[(row-2)*taille+col+2]->getHasPion())
            { 
                //on verifie ya pas de pion sur point de chute
                boitePionEnnemi.append(currentBox->game->tab_damier[(row-1)*taille+col+1]);
                location.append(currentBox->game->tab_damier[(row-2)*taille+col+2]);
                //boxSetting(location.last());
            }
        }

        //si le pion ne peut manger aucun pion on regarde s'il peut avancer a droite ou a gauche
        if(location.size()==0 && boitePionEnnemi.size()==0)
        {
            if(row< taille-1 && col>0 && (!currentBox->game->tab_damier[(row+1)*taille+col-1]->getHasPion()))
            { 
                //gauche
                qDebug()<<"fonction moves() possibilite d'avancer a gch qd3";
                location.append(currentBox->game->tab_damier[(row+1)*taille+col-1]);
                boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());
            }
            if(row< taille-1 && col<taille-1 && (!currentBox->game->tab_damier[(row+1)*taille+col+1]->getHasPion()))
            { 
                //droite
                qDebug()<<" fonction moves() possibilite d'avancer a dte qd4";
                location.append(currentBox->game->tab_damier[(row+1)*taille+col+1]);
                boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());
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
QList<Boite *> Pion::getLocation()
{
    return location;
}
QList<Boite *> Pion::getEnnemis()
{
    return boitePionEnnemi;
}
void Pion::decolor()
{
    for(size_t i = 0, n = currentBox->game->tab_damier.size(); i < n;i++) {
         currentBox->game->tab_damier[i]->resetOriginalColor();
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

