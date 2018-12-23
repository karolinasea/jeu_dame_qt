#include "boite.hpp"
#include <QDebug>
#include "game.hpp"

//extern Game *game;
Boite::Boite(Game *g, QGraphicsItem *parent):QGraphicsRectItem(parent),game(g)
{
    //making the Square CHess Box
    setRect(0,0,game->largeurBoite,game->largeurBoite);
    brush.setStyle(Qt::SolidPattern);
    setZValue(-1);
    setHasPion(false);

    currentPiece = nullptr;
}

Boite::~Boite()
{
    delete this;
}

void Boite::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
      //  qDebug() << getpionColor();
        //Deselecting counter part of pion
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //if selected
        if(game->pieceToMove){
            //if same team
            if(this->getPionCouleur() == game->pieceToMove->getSide())
                return;
            //pièce à manger on vérifie
            QList <Boite *> movLoc = game->pieceToMove->movelocation();
            //TO make sure the selected box is in move zone
            int check = 0;
            for(unsigned int i = 0, n = movLoc.size(); i < n;i++) {
                if(movLoc[i] == this) {
                    check++;

                }
            }
            // if not prsent return
            if(check == 0)
                return;
            //change the color back to normal
             game->pieceToMove->decolor();

             //this is to eat or consume the enemy present inn the movable region
            if(this->getHasPion()){
                this->currentPiece->setIsPlaced(false);
                this->currentPiece->setCurrentBoite(nullptr);
                game->placeInDeadPlace(this->currentPiece);

            }
            //changing the new stat and resetting the previous left region
            game->pieceToMove->getCurrentBoite()->setHasPion(false);
            game->pieceToMove->getCurrentBoite()->currentPiece = nullptr;
            game->pieceToMove->getCurrentBoite()->resetOriginalColor();
            placePiece(game->pieceToMove);

            game->pieceToMove = nullptr;
            //changing turn
            game->changeTurn();
            //checkForCheck();
        }
        //Selecting couterpart of the pion
        /*else if(this->getHasPion())
        {
            this->currentPiece->mousePressEvent(event);
        }*/
}

void Boite::setCouleur(QColor color)
{
    brush.setColor(color);
    setBrush(color);
}


void Boite::placePiece(Pion *piece)
{

    piece->setPos(x()+game->largeurBoite/2- piece->pixmap().width()/2  ,y()+game->largeurBoite/2-piece->pixmap().width()/2);
    piece->setCurrentBoite(this);
    setHasPion(true,piece);
    currentPiece = piece;


}

void Boite::resetOriginalColor()
{
    setCouleur(couleurDorigine);
}


void Boite::setOriginalColor(QColor value)
{
    couleurDorigine = value;
    setCouleur(couleurDorigine);
}

bool Boite::getHasPion()
{
    return hasPion;
}

void Boite::setHasPion(bool hasOne, Pion *piece)
{
    hasPion = hasOne;
    if(hasOne)
        setPionCouleur(piece->getSide());
    else
        setPionCouleur(Couleur::None);
}

void Boite::checkForCheck()
{
    int c = 0;
    QList <Pion *> pList = game->alivePiece;
    for(size_t i = 0,n=pList.size(); i < n; i++ ) {

      /*  King * p = dynamic_cast<King *> (pList[i]);
        if(p){
            continue;
        }
        pList[i]->moves();
        pList[i]->decolor();
        QList <boite *> bList = pList[i]->moveLocation();
        for(size_t j = 0,n = bList.size(); j < n; j ++) {
            King * p = dynamic_cast<King *> (bList[j]->currentPiece);
            if(p) {
                if(p->getSide() == pList[i]->getSide())
                    continue;
                bList[j]->setColor(Qt::blue);
                pList[i]->getCurrentBox()->setColor(Qt::darkRed);
                if(!game->check->isVisible())
                    game->check->setVisible(true);
                else{
                    bList[j]->resetOriginalColor();
                    pList[i]->getCurrentBox()->resetOriginalColor();
                    game->gameOver();
                }
                c++;

            }
        }*/


    }
    if(!c){
        game->check->setVisible(false);
        for(size_t i = 0,n=pList.size(); i < n; i++ )
            pList[i]->getCurrentBoite()->resetOriginalColor();
    }
}

Couleur Boite::getPionCouleur()
{
    return couleurPion;
}

void Boite::setPionCouleur(Couleur value)
{
    couleurPion = value;
}
