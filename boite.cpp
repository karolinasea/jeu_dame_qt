#include "boite.h"
#include <QDebug>
#include "game.h"
#include <qpropertyanimation.h>

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
            //Deselecting  pion
            if(currentPiece == game->pieceToMove && currentPiece)
            {
                currentPiece->mousePressEvent(event);
                return;
            }

            //si un pion est deja selectionné, il a surement cliqué sur une case d'arrivée
            if(game->pieceToMove)
            {
                //if same team
                if(this->getPionCouleur() == game->pieceToMove->getSide())
                {
                    return;
                }

                //pièce à manger on vérifie
                QVector <Boite *> movLoc_a;
                QVector <Boite *> movLoc_b;
                QVector <Boite *> movLoc_c;
                QVector <Boite *> movLoc_d;
                movLoc_a.append(game->pieceToMove->gene->liste_avant_g);
                movLoc_b.append(game->pieceToMove->gene->liste_avant_d);
                movLoc_c.append(game->pieceToMove->gene->liste_arr_d);
                movLoc_d.append(game->pieceToMove->gene->liste_arr_g);
                char a,b,c,d,t1 =0, t2 = 0, maxi, i=0, check=0;
                a=movLoc_a.size();
                b=movLoc_b.size();
                c=movLoc_c.size();
                d=movLoc_d.size();

                t1 = (a > b? a : b);
                    t2 = (c > d? c : d);
                    maxi = (t1 > t2? t1 : t2);
                    //qDebug()<<"t1= "<<t1<<" t2= "<<" maxi= "<<maxi;
                    if (!movLoc_a.isEmpty()&&maxi==0){
                        qDebug()<<"q1011";
                        if (this==movLoc_a.first()&&game->pieceToMove->gene->liste_avant_g_enn.isEmpty())
                        {
                            qDebug()<<"q1012";
                            check=1;
                        }
                      }
                    if (!movLoc_b.isEmpty()&&maxi==0){
                        qDebug()<<"q1013";
                        if (this==movLoc_b.first()&&game->pieceToMove->gene->liste_avant_d_enn.isEmpty())
                        {
                            qDebug()<<"q1014";
                            check=1;
                        }
                       }
                    if (maxi==a){
                        if (this==movLoc_a.last()){
                            qDebug()<<"maxi = a";
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
                            qDebug()<<"maxi=b";
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
                            qDebug()<<"maxi=c";
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
                        qDebug()<<"maxi=d";
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
               // QList <Boite *> ennemisLoc = game->pieceToMove->getEnnemis();
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

                //changing the new stat and resetting the previous left region
                game->pieceToMove->getCurrentBoite()->setHasPion(false);
                game->pieceToMove->getCurrentBoite()->currentPiece = nullptr;
                //game->pieceToMove->getCurrentBoite()->resetOriginalColor();
                placePiece(game->pieceToMove);


                game->pieceToMove = nullptr;
                //changing turn
                game->changeTurn();
             }
            //Selecting couterpart of the pion
            else if(this->getHasPion())
            {
                this->currentPiece->mousePressEvent(event);
            }
        //transformation en dame dans boite mousepressed event a la fin
        int count;
        int taille = game->nbCases;
        //on regarde si il y a une boite du row=0 qui contient un pion blanc et si c est le cas on convertit le pion blanc
        for(count=0; count<taille; count++)
        {
             if(game->tab_damier[0*taille+count]==this)
             {
                  if(getHasPion() && getPionCouleur()==Couleur::Blanc && !currentPiece->isDame)
                  {
                        currentPiece->conversionDame();
                        //currentPiece->isDame==true;
                  }
             }
         }
         for(count=0; count<taille; count++)
         {
              if(game->tab_damier[(taille-1)*taille+count]==this)
              {
                   if(getHasPion() && getPionCouleur()==Couleur::Noir && !currentPiece->isDame)
                   {
                        currentPiece->conversionDame();
                        //currentPiece->isDame==true;
                    }
               }
          }
        qDebug()<<"alivepiece.size"<<game->alivePiece.size();
        //check if game is over:
                int countDameN = 0, countDameB = 0, countB = 0, countN = 0;
                for(size_t i = 0, n = game->alivePiece.size(); i<n; i++)
                {
                    if(game->alivePiece[i]->isDame && game->alivePiece[i]->getSide()==Couleur::Noir)
                    {
                        countDameN++;
                    }
                    if(game->alivePiece[i]->isDame && game->alivePiece[i]->getSide()==Couleur::Blanc)
                    {
                        countDameB++;
                    }
                    if(!game->alivePiece[i]->isDame && game->alivePiece[i]->getSide()==Couleur::Blanc)
                    {
                        countB++;
                    }
                    if(!game->alivePiece[i]->isDame && game->alivePiece[i]->getSide()==Couleur::Noir)
                    {
                        countN++;
                    }
                }
                //qDebug()<<"countN "<<countN<<"countB "<<countB<<"countDameB "<<countDameB<<"countDameN "<<countDameN;
                if(countDameB==0 && countDameN==0 && countN>0 && countB==0)
                {
                    qDebug()<<"les noirs gagnent";
                    game->resetDamier();
                }
                if(countDameB==0 && countDameN==0 && countB>0 && countN==0)
                {
                    qDebug()<<"les blancs gagnent";
                    game->resetDamier();
                }
                if(countDameB>0 && countDameN==0 && countB>=0 && countN==0)
                {
                    qDebug()<<"les blancs gagnent";
                    game->resetDamier();
                }
                if(countDameB>=0 && countDameN==0 && countB>0 && countN==0)
                {
                    qDebug()<<"les blancs gagnent";
                    game->resetDamier();
                }
                if(countDameN>0 && countDameB==0 && countN>=0 && countB==0)
                {
                    qDebug()<<"les noirs gagnent";
                    game->resetDamier();
                }
                if(countDameN>=0 && countDameB==0 && countN>0 && countB==0)
                {
                    qDebug()<<"les noirs gagnent";
                    game->resetDamier();
                    game->gameIsOver->setVisible(true);
                }
                if(countDameB>0 && countB==0 && countDameN==0 && countN==0)
                {
                    qDebug()<<"les blancs gagnent";
                    game->resetDamier();

                }
                if(countDameN>0 && countN==0 && countDameB==0 && countB==0)
                {
                    qDebug()<<"les noirs gagnent";
                    game->resetDamier();
                }
                if(countDameB>0 && countB>0 && countDameN==0 && countN==0)
                {
                    qDebug()<<"les blancs gagnent";
                    game->resetDamier();
                }
                if(countDameN>0 && countN>0 && countDameB==0 && countB==0)
                {
                    qDebug()<<"les noirs gagnent";
                    game->resetDamier();
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

Couleur Boite::getPionCouleur()
{
    return couleurPion;
}

void Boite::setPionCouleur(Couleur value)
{
    couleurPion = value;
}
