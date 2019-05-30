#include "boite.h"
#include <QDebug>
#include "game.h"
//#include <qpropertyanimation.h>
#include <QPropertyAnimation>

//extern Game *game;
Boite::Boite(Game *g, QGraphicsItem *parent):QGraphicsRectItem(parent),game(g)
{
    //making the Square checker Box
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
        //Deselecting  pion
        if(currentPiece == game->pieceToMove && currentPiece){

            currentPiece->mousePressEvent(event);
            return;
        }

        //si un pion est deja selectionné, il a surement cliqué sur une case d'arrivée
        if(game->pieceToMove){
            //if same team
            if(this->getPionCouleur() == game->pieceToMove->getSide())
                return;
            //pièce à manger on vérifie
            QVector <Boite *> movLoc_a;
                    QVector <Boite *> movLoc_b;
                    QVector <Boite *> movLoc_c;
                    QVector <Boite *> movLoc_d;
            movLoc_a.append(game->pieceToMove->gene->liste_avant_g);
            movLoc_b.append(game->pieceToMove->gene->liste_avant_d);
            movLoc_c.append(game->pieceToMove->gene->liste_arr_d);
            movLoc_d.append(game->pieceToMove->gene->liste_arr_g);
            char a,b,c,d,t1,t2,maxi,i=0,check=0;
            a=movLoc_a.size();
            b=movLoc_b.size();
            c=movLoc_c.size();
            d=movLoc_d.size();

            t1 = (a > b? a : b);
                t2 = (c > d? c : d);
                maxi = (t1 > t2? t1 : t2);

                if (!movLoc_a.isEmpty()){
                    if (this==movLoc_a.first()&&game->pieceToMove->gene->liste_avant_g_enn.isEmpty())
                        check=1;
                  }
                if (!movLoc_b.isEmpty()){
                    if (this==movLoc_b.first()&&game->pieceToMove->gene->liste_avant_d_enn.isEmpty())
                        check=1;
                   }
                if (maxi==a){
                    if (this==movLoc_a.last()){
                        for(int n = game->pieceToMove->gene->liste_avant_g_enn.size(); i < n;i++) {
                        game->pieceToMove->gene->liste_avant_g_enn[i]->currentPiece->setIsPlaced(false);
                        game->pieceToMove->gene->liste_avant_g_enn[i]->currentPiece->setCurrentBoite(nullptr);
                        game->placeInDeadPlace(game->pieceToMove->gene->liste_avant_g_enn[i]->currentPiece);
                       game->pieceToMove->gene->liste_avant_g_enn[i]->setHasPion(false);
                        game->pieceToMove->gene->liste_avant_g_enn[i]->currentPiece = nullptr;
                        }check=1;
                    }
                }
                if (maxi==b){
                    if (this==movLoc_b.last()){
                        for(int n = game->pieceToMove->gene->liste_avant_d_enn.size(); i < n;i++) {
                        game->pieceToMove->gene->liste_avant_d_enn[i]->currentPiece->setIsPlaced(false);
                        game->pieceToMove->gene->liste_avant_d_enn[i]->currentPiece->setCurrentBoite(nullptr);
                        game->placeInDeadPlace(game->pieceToMove->gene->liste_avant_d_enn[i]->currentPiece);
                       game->pieceToMove->gene->liste_avant_d_enn[i]->setHasPion(false);
                        game->pieceToMove->gene->liste_avant_d_enn[i]->currentPiece = nullptr;
                        }check=1;
                    }
                }
                if (maxi==c){
                    if (this==movLoc_c.last()){
                        for(int n = game->pieceToMove->gene->liste_arr_d_enn.size(); i < n;i++) {
                        game->pieceToMove->gene->liste_arr_d_enn[i]->currentPiece->setIsPlaced(false);
                        game->pieceToMove->gene->liste_arr_d_enn[i]->currentPiece->setCurrentBoite(nullptr);
                        game->placeInDeadPlace(game->pieceToMove->gene->liste_arr_d_enn[i]->currentPiece);
                       game->pieceToMove->gene->liste_arr_d_enn[i]->setHasPion(false);
                        game->pieceToMove->gene->liste_arr_d_enn[i]->currentPiece = nullptr;
                        }check=1;
                    }
                }
                if (maxi==d){
                    if (this==movLoc_d.last()){
                        for(int n = game->pieceToMove->gene->liste_arr_g_enn.size(); i < n;i++) {
                        game->pieceToMove->gene->liste_arr_g_enn[i]->currentPiece->setIsPlaced(false);
                        game->pieceToMove->gene->liste_arr_g_enn[i]->currentPiece->setCurrentBoite(nullptr);
                        game->placeInDeadPlace(game->pieceToMove->gene->liste_arr_g_enn[i]->currentPiece);
                       game->pieceToMove->gene->liste_arr_g_enn[i]->setHasPion(false);
                        game->pieceToMove->gene->liste_arr_g_enn[i]->currentPiece = nullptr;
                        }check=1;
                    }
                }

            //pièce ou ya les ennemis à enlever
            QList <Boite *> ennemisLoc = game->pieceToMove->getEnnemis();
            //TO make sure the selected box is in move zone
            //char check = 0;
            //int i=0;
            /*for(int n = movLoc.size(); i < n;i++) {

                if(movLoc[i] == this) {
                    check++;
                    break;

                }
            }*/
            // if not prsent return
            if(check == 0)
                return;
            //change the color back to normal
             game->pieceToMove->decolor();

             //this is to eat or consume the enemy present in the movable region


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
        else if(this->getHasPion())
        {
            this->currentPiece->mousePressEvent(event);
        }

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
    for(size_t i = 0, n=pList.size(); i < n; i++ ) {

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
    if(!c)
    {
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
