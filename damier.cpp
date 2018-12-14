#include "damier.hpp"
#include "boite.hpp"

#include "pawn.hpp"

//extern Game *game;
damier::damier(Game *g, int param):game(g), param(param)
{

    setUpBlack();
    setUpWhite();
}
void damier::drawBoxes(int x,int y)
{
    int shift;
    if (param==8)
        shift = 100;
    else if (param==10)
        shift=80;
    else if (param==12)
        shift=67;
    for(int i = 0; i < param; i++) {
        for(int j = 0; j < param; j++)
        {
            boite *box = new boite(game, shift);
            game->collection[i*12+j] = box;
            box->rowLoc = i;
            box->colLoc = j;
            box->setPos(x+shift*j,y+shift*i);
            if((i+j)%2==0)
                box->setOriginalColor(Qt::white);
            else
                box->setOriginalColor(Qt::darkGray);
            game->addToScene(box);



        }
    }

}


void damier::addChessPiece() {
    int j=1;

    for(int i = 0; i < param; i++) {
        j-=param;
        (j==1)?j=0:j=1;
        for(; j < param; j+=2)
        {

            boite *box =game->collection[i*12+j];
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

void damier::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pawn(Couleur::Blanc);
        white.append(piece);
    }


}

void damier::setUpBlack()
{
    ChessPiece *piece;

    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pawn(Couleur::Noir);
        black.append(piece);
    }
}


void damier::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            boite *box =game->collection[i*12+j];
            box->setHasChessPiece(false);
            box->setChessPieceColor(Couleur::None);
            box->currentPiece = nullptr;
            if(i < 2) {

                box->placePiece(black[k]);
                black[k]->setIsPlaced(true);
                black[k]->firstMove = true;
                game->alivePiece.append(black[k++]);

            }
            if(i > 5) {

                box->placePiece(white[h]);
                white[h]->setIsPlaced(true);
                white[h]->firstMove = true;
                game->alivePiece.append(white[h++]);

            }

        }
    }
}
