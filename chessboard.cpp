#include "chessboard.hpp"
#include "chessbox.hpp"

#include "pawn.hpp"

//extern Game *game;
ChessBoard::ChessBoard(Game *g, int param):game(g), param(param)
{

    setUpBlack();
    setUpWhite();
}
void ChessBoard::drawBoxes(int x,int y)
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
            ChessBox *box = new ChessBox(game, shift);
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


void ChessBoard::addChessPiece() {
    int j=1;

    for(int i = 0; i < param; i++) {
        j-=param;
        (j==1)?j=0:j=1;
        for(; j < param; j+=2)
        {

            ChessBox *box =game->collection[i*12+j];
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

void ChessBoard::setUpWhite()
{
    ChessPiece *piece;
    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pawn(Couleur::Blanc);
        white.append(piece);
    }


}

void ChessBoard::setUpBlack()
{
    ChessPiece *piece;

    for(int i = 0; i < 3*param/2; i++) {
        piece = new Pawn(Couleur::Noir);
        black.append(piece);
    }
}


void ChessBoard::reset() {
    int k = 0; int h = 0;
    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++)
        {

            ChessBox *box =game->collection[i*12+j];
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
