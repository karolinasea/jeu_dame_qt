#include "damier.hpp"
#include "boite.hpp"

#include "pion.hpp"

//extern Game *game;
Damier::Damier(Game *g, int param):game(g), param(param)
{

    setUpBlack();
    setUpWhite();
}
void Damier::drawBoites(int x,int y)
{

    for(int i = 0; i < param; i++) {
        for(int j = 0; j < param; j++)
        {
            Boite *box = new Boite(game);
            game->tab_damier.append(box);
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+game->largeurBoite*j,y+game->largeurBoite*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::white);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);



        }
    }

}


void Damier::addPion() {
    int j=1;

    for(int i = 0; i < param; i++) {
        j-=param;
        (j==1)?j=0:j=1;
        for(; j < param; j+=2)
        {

            Boite *box =game->tab_damier[i*12+j];
            if(i < 3) {
                static int k;
                box->placePiece(black[k]);
                game->alivePiece.append(black[k]);
                game->addToScene(black[k++]);
            }
            if(i > param-4) {
                static int h;
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
    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pion(Couleur::Blanc);
        white.append(piece);
    }


}

void Damier::setUpBlack()
{
    Pion *piece;

    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pion(Couleur::Noir);
        black.append(piece);
    }
}


void Damier::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            Boite *box =game->tab_damier[i*12+j];
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
    }
}
