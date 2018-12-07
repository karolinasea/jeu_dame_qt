#include "pawn.hpp"
#include "game.hpp"
#include <QDebug>
#include <typeinfo>

extern Game * game;
Pawn::Pawn(Couleur team,QGraphicsItem *parent):ChessPiece(team,parent)
{
    setImage();
    firstMove = true;
}

void Pawn::setImage()
{
    if(side == Couleur::Blanc)
        setPixmap(QPixmap(":/images/pawn1.png"));
    else
        setPixmap(QPixmap(":/images/pawn.png"));
}



void Pawn::moves()
{
    location.clear();

    int row = this->getCurrentBox()->rowLoc;

    int col = this->getCurrentBox()->colLoc;
    if(this->getSide() == Couleur::Blanc)  {
        if(col > 0 && row > 0 && game->collection[(row-1)*12+col-1]->getChessPieceColor() == Couleur::Noir) {
            location.append(game->collection[(row-1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row > 0 && game->collection[(row-1)*12+col+1]->getChessPieceColor() == Couleur::Noir) {
            location.append(game->collection[(row-1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row>0 && (!game->collection[(row-1)*12+col]->getHasChessPiece())) {
            location.append(game->collection[(row-1)*12+col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[(row-2)*12+col]->getHasChessPiece()){
                location.append(game->collection[(row-2)*12+col]);
                boxSetting(location.last());
            }
        }

    }
    else{
        if(col > 0 && row < 7 && game->collection[(row+1)*12+col-1]->getChessPieceColor() == Couleur::Blanc) {//left
            location.append(game->collection[(row+1)*12+col-1]);
            boxSetting(location.last());
        }
        if(col < 7 && row <  7 && game->collection[(row+1)*12+col+1]->getChessPieceColor() == Couleur::Blanc) {//right
            location.append(game->collection[(row+1)*12+col+1]);
            boxSetting(location.last());
        }
        if(row<7 && (!game->collection[(row+1)*12+col]->getHasChessPiece())) {
            location.append(game->collection[(row+1)*12+col]);
            boxSetting(location.last());
            if(firstMove && !game->collection[(row+2)*12+col]->getHasChessPiece()){
                location.append(game->collection[(row+2)*12+col]);
                boxSetting(location.last());
            }

        }

    }

}


