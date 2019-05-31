#include "damier.h"
#include<QDebug>

//extern Game *game;
Damier::Damier(Game *g, int param):game(g), param(param)
{
    setUpBlack();
    setUpWhite();
}
void Damier::drawBoites(int x,int y)
{

    for(int i = 0; i < param; i++)
    {
        for(int j = 0; j < param; j++)
        {
            Boite *box = new Boite(game);
            game->tab_damier.append(box);
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+game->largeurBoite*j,y+game->largeurBoite*i);
            if((i+j)%2==0)
            {
                box->setOriginalColor(Qt::white);
            }
            else
            {
                box->setOriginalColor(Qt::darkGray);
            }
            game->addToScene(box);
        }
    }
}


void Damier::addPion()
{
   int r, c, k=0, h=0;

        if(param==8)
        {
            for(r=0; r<3; r++)
            {
                if(r==1) c=0;
                else c=1;
                for(; c<param; c+=2)
                {
                    Boite *box = game->tab_damier[r*param+c];
                    box->placePiece(black[k]);
                    game->alivePiece.append(black[k]);
                    game->addToScene(black[k++]);
                }
            }
            for(r=5; r<param; r++)
            {
                if(r==6) c=1;
                else c=0;
                for(; c<param; c+=2)
                {
                    Boite *box = game->tab_damier[r*param+c];
                    box->placePiece(white[h]);
                    game->alivePiece.append(white[h]);
                    game->addToScene(white[h++]);
                }
            }
        }

        if(param==10)
        {
            //qDebug()<<"taille de la liste black"<<black.size();
            for(r=0; r<4; r++)
            {
                if(r==1 || r==3) c=0;
                else c=1;
                for(; c<param; c+=2)
                {
                    Boite *box = game->tab_damier[r*param+c];
                    box->placePiece(black[k]);
                    game->alivePiece.append(black[k]);
                    game->addToScene(black[k++]);
                }
            }
            for(r=6; r<param; r++)
            {
                if(r==7 || r==9) c=0;
                else c=1;
                for(; c<param; c+=2)
                {
                    Boite *box = game->tab_damier[r*param+c];
                    box->placePiece(white[h]);
                    game->alivePiece.append(white[h]);
                    game->addToScene(white[h++]);
                }
            }
        }
}

void Damier::setUpWhite()
{
    Pion *piece;
    if(param==8)
    {
        for(int i=0; i<12; i++)
        {
            piece = new Pion(Couleur::Blanc);
            white.append(piece);
        }
    }
    if(param==10)
    {
        for(int i=0; i<20; i++)
        {
            piece = new Pion(Couleur::Blanc);
            white.append(piece);
        }
    }
   /* if(param==12)
    {
        for(int i=0; i<24; i++)
        {
            piece = new Pion(Couleur::Blanc);
            white.append(piece);
        }
    }*/
}

void Damier::setUpBlack()
{
    Pion *piece;
    if(param==8)
    {
        for(int i=0; i<12; i++)
        {
            piece = new Pion(Couleur::Noir);
            black.append(piece);
        }
    }
    if(param==10)
    {
        for(int i=0; i<20; i++)
        {
            piece = new Pion(Couleur::Noir);
            black.append(piece);
        }
    }
    /*if(param==12)
    {
        for(int i=0; i<24; i++)
        {
            piece = new Pion(Couleur::Noir);
            black.append(piece);
        }
    }*/
}


void Damier::reset()
{
    qDebug()<<"dans reset damier classe Damier";

   qDeleteAll(black);
   qDeleteAll(white);
    //qDeleteAll(black.begin(), black.end());
    //qDeleteAll(white.begin(), white.end());

    int r, c;
    for(r=0; r<game->nbCases; r++)
    {
        qDebug()<<"dans reset damier classe Damier 1";
        for(c=0; c<game->nbCases; c++)
        {
            qDebug()<<"dans reset damier classe Damier 2";
            if(game->tab_damier[r*game->nbCases+c]->getHasPion())
            {
                qDebug()<<"dans reset damier classe Damier 3";
                game->removeFromScene(game->tab_damier[r*game->nbCases+c]);
                game->tab_damier[r*game->nbCases+c] = nullptr;
            }
        }
    }
qDebug()<<"dans reset damier classe Damier 4";
    //white.clear();
    //black.clear();



    /*int k = 0; int h = 0;
        for(int i = 0; i < 8; i++) {
            for(int j = 0; j < 8; j++)
            {

                Boite *box =game->tab_damier[i*8+j];
                box->setHasPion(false);
                box->setPionCouleur(Couleur::None);
                box->currentPiece = nullptr;
                if(i < 2) {

                    box->placePiece(black[k]);
                    black[k]->setIsPlaced(true);
                    game->alivePiece.append(black[k++]);

                }
                if(i > 5) {

                    box->placePiece(white[h]);
                    white[h]->setIsPlaced(true);
                    game->alivePiece.append(white[h++]);

                }

            }
        }*/


    /*int k = 0; int h = 0;
    int r, c;
    int taille = game->nbCases;
    qDebug()<<"dans reset damier classe Damier";
    for(r = 0; r < taille; r++) {
        for(c = 0; c < taille-1; c++)
        {
            qDebug()<<"dans reset damier classe Damier 1";
            Boite *box =game->tab_damier[r*taille+c];
            box->setHasPion(false);
            box->setPionCouleur(Couleur::None);
            box->currentPiece = nullptr;
            if(r < 3)
            {
                qDebug()<<"dans reset damier classe Damier 2";
                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                game->alivePiece.append(black[k++]);
            }
            qDebug()<<"dans reset damier classe Damier 4";
            if(r > 4)
            {
                qDebug()<<"dans reset damier classe Damier 3";
                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                game->alivePiece.append(white[h++]);
            }
        }
    }*/
    //int r, c;
    //int h=0, k=0;

    /*int taille = game->nbCases;
        for(r=0; r<taille; r++)
        {
            qDebug()<<"dans reset damier classe Damier A";
            for(c=0; c<taille; c++)
            {
                qDebug()<<"dans reset damier classe Damier B";
                if(game->tab_damier[r*taille+c]->getHasPion())
                {
                    qDebug()<<"dans reset damier classe Damier C";
                    game->removeFromScene(game->tab_damier[r*taille+c]->currentPiece);
                    game->tab_damier[r*taille+c]->setHasPion(false);
                    game->tab_damier[r*taille+c]->setPionCouleur(Couleur::None);
                    game->tab_damier[r*taille+c]->currentPiece = nullptr;
                }
            }
        }
       */
}
