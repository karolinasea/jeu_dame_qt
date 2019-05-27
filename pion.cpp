#include "pion.h"
#include "game.h"
#include "generateur.h"
#include <QDebug>
#include <typeinfo>


Pion::Pion (Couleur team,QGraphicsItem *parent) : QGraphicsPixmapItem(parent), side(team), isPlaced(true), isDame(false)
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap("C:\\Users\\carole\\Documents\\build-CHECKERS2-Desktop_Qt_5_12_2_MinGW_32_bit2-Debug\\debug\\pawn1.png"));
    else
        setPixmap(QPixmap("C:\\Users\\carole\\Documents\\build-CHECKERS2-Desktop_Qt_5_12_2_MinGW_32_bit2-Debug\\debug\\pawn.png"));

}

void Pion::conversionDame ()
{
    if(side == Couleur::Blanc)
    {
        setPixmap(QPixmap("C:\\Users\\carole\\Documents\\build-CHECKERS2-Desktop_Qt_5_12_2_MinGW_32_bit2-Debug\\debug\\dame_blanche.png"));
    }
    else if(side == Couleur::Noir)
    {
        setPixmap(QPixmap("C:\\Users\\carole\\Documents\\build-CHECKERS2-Desktop_Qt_5_12_2_MinGW_32_bit2-Debug\\debug\\dame_noire.png"));
    }

}

void Pion::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //si deja mangee ou pas le tour de la couleur
    //if pawn of wrong color or not on the board anymore
    // currentBox est un attribut de pion de type Boite
    //pieceToMove est un pion
    /*if((!getIsPlaced() )|| ( (currentBox->game->getTurn() != this->getSide()) && (!currentBox->game->pieceToMove)) )
    {
        //event->ignore();
        return;
    }*/

    //selecting pieces
    if(currentBox->game->pieceToMove == nullptr)
    {
        currentBox->game->pieceToMove = this;
        if ((currentBox->game->getTurn()==Couleur::Noir && currentBox->game->pieceToMove->getSide()==Couleur::Blanc) || (currentBox->game->getTurn()==Couleur::Blanc && currentBox->game->pieceToMove->getSide()==Couleur::Noir))
        {
            qDebug()<<"wrong color compare to the turn";
            currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
            currentBox->game->pieceToMove->decolor();
            currentBox->game->pieceToMove = nullptr;
            //event->ignore();
            //return;
        }
        else
        {
            qDebug()<<"else";
            currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
            currentBox->game->pieceToMove->moves();
        }
    }
    if(currentBox->game->pieceToMove != nullptr)
    {
        currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        currentBox->game->pieceToMove->decolor();
        currentBox->game->pieceToMove = this;
        if ((currentBox->game->getTurn()==Couleur::Noir && currentBox->game->pieceToMove->getSide()==Couleur::Blanc) || (currentBox->game->getTurn()==Couleur::Blanc && currentBox->game->pieceToMove->getSide()==Couleur::Noir))
        {
            qDebug()<<"wrong color compare to the turn";
            currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
            currentBox->game->pieceToMove->decolor();
            currentBox->game->pieceToMove = nullptr;
            //event->ignore();
            //return;
        }
        else
        {
            qDebug()<<"else";
            int j;
            int taille = currentBox->game->nbCases;
            currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
            currentBox->game->pieceToMove->moves();
            for(j=1; j<taille-2; j+=2)
            {
                if(currentBox->game->tab_damier[0*taille+j]->getPionCouleur() == Couleur::Blanc)
                {
                        this->conversionDame();
                        this->isDame==true;
                }
            }
            for(j=0; j<taille-2; j+=2)
            {
                if(currentBox->game->tab_damier[(taille-1)*taille+j]->getPionCouleur() == Couleur::Noir)
                {
                        this->conversionDame();
                        this->isDame==true;
                }
            }

        }
    }

    //si on est au debut du jeu et donc pieceToMove=nullptr et donc que les blancs doivent commencer
    /*if(currentBox->game->pieceToMove==nullptr)
    {
        qDebug()<<"==nullptr";
        currentBox->game->pieceToMove = this;
        if (currentBox->game->pieceToMove->getSide()==Couleur::Noir)
        {
            qDebug()<<"if it s the first turn and we click on black piece";
            //event->ignore();
            currentBox->game->pieceToMove = nullptr;
            //return;
        }
        else
        {
            qDebug()<<"==nullptr and else";
            currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
            currentBox->game->pieceToMove->moves();
        }
    }

    if(currentBox->game->pieceToMove!=nullptr)
    {
        qDebug()<<"!=nullptr";
        currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        currentBox->game->pieceToMove->decolor();
        currentBox->game->pieceToMove = this;
        if ((currentBox->game->getTurn()==Couleur::Noir && currentBox->game->pieceToMove->getSide()==Couleur::Blanc) || (currentBox->game->getTurn()==Couleur::Blanc && currentBox->game->pieceToMove->getSide()==Couleur::Noir))
        {
            qDebug()<<"!=nullptr and wrong color compare to the turn";
            currentBox->game->pieceToMove = nullptr;
            //event->ignore();
            //return;
        }
        else
        {
            qDebug()<<"!=nullptr and else";
            currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
            currentBox->game->pieceToMove->moves();
        }
    }*/



    //Deselect
   /* if(this == currentBox->game->pieceToMove)
    {
        currentBox->game->pieceToMove->getCurrentBoite()->resetOriginalColor();
        currentBox->game->pieceToMove->decolor();
        currentBox->game->pieceToMove = nullptr;
       return;
    }

    //selecting
    if(!currentBox->game->pieceToMove)
    {
        currentBox->game->pieceToMove = this;
        currentBox->game->pieceToMove->getCurrentBoite()->setCouleur(Qt::red);
        currentBox->game->pieceToMove->moves();
    }*/

        //sa va direct a move donc prend en compte la position de un seul pion seulement
        //on veut pouvoir prendre en compte la position de tous les pions, de maniere a ce que quand il y a un pion qui peut
        //manger on ne puisse pas voir de chemin (cases colorees) si on selectionne un autre pion que celui qui peut/doit manger
        //de maniere a ce qu on puisse voir les cases colorees seulement pour les pions qui peuvent manger si il y en a
        //ou seulement sur le/les pions qui peut/peuvent manger le plus de pions a la fois

        //donc il faudrait faire un generateur de coup pour tous les pions
        /*gene = new generateur(taille, row, col, currentBox->game->tab_damier, this->getSide());

        //boucles qui rempli les listes du generateurs pour chaque pion (de la couleur qui a le tour)

    //Consuming counterPart of the boite   UTILITĂ© ??
    else if(this->getSide() != currentBox->game->pieceToMove->getSide()){
        qDebug()<<"oui ";
        this->getCurrentBoite()->mousePressEvent(event);
    }*/
}

void Pion::moves()
{
    location.clear(); /*Removes all items from the list location which is an attribute of class Pion*/
    boitePionEnnemi.clear(); /*Removes all items from the list boitePionEnnemi which is an attribute of class Pion*/

    int row = this->getCurrentBoite()->rowLoc; //get the row number of the box on which the pawn is placed
    char taille = currentBox->game->nbCases; //nbCases is the size of the board (8x8 or 10x10..)
    int col = this->getCurrentBoite()->colLoc; //get the column number of the box on which the pawn is placed
    int j;


        /*for(j=1; j<taille-2; j+=2)
        {
            if(currentBox->game->tab_damier[0*taille+j]->getPionCouleur() == Couleur::Blanc)
            {
                    this->conversionDame();
                    this->isDame==true;
            }
        }
        for(j=0; j<taille-2; j+=2)
        {
            if(currentBox->game->tab_damier[(taille-1)*taille+j]->getPionCouleur() == Couleur::Noir)
            {
                    this->conversionDame();
                    this->isDame==true;
            }
        }*/


    //tab_damier est le nom d'un attribut de game et est de type QVector<Boites>
    //tab_damier est la liste des boites du damier ???? not sure
    //gene = new generateur(taille, row, col, currentBox->game->tab_damier, this->getSide());
    //rajout d'un attribut a generateur pour lui dire si le pion est une dame ou non
    gene = new generateur(taille, row, col, currentBox->game->tab_damier, this->getSide(), this->isDame);
    gene->remplirListes();

    //return ;
    /*stops the fonction to go to remplirListes and then remplirListes colors the boites/cases
    sur lesquelles le pion selectionne peut aller*/

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
        //si le pion est dans la premiere range il devient une dame
        if(row == 0)
        {
            this->conversionDame();
            this->isDame==true;
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
        //si le pion est dans la premiere range il devient une dame
        if(currentBox->game->nbCases==8 && row == 7)
        {
            this->conversionDame();
            this->isDame==true;
        }
        if(currentBox->game->nbCases==10 && row == 9)
        {
            this->conversionDame();
            this->isDame==true;
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

