#ifndef boite_H
#define boite_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QGraphicsSceneMouseEvent>


#include "enumCouleur.hpp"
#include "chesspiece.hpp"


class ChessPiece;
class Game;
class boite:public QGraphicsRectItem
{
public:

    //Constructor
    boite(Game *g, int taille, QGraphicsItem *parent=nullptr);
    ~boite();


    //public member function
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void setColor(QColor color);
    void placePiece(ChessPiece *piece);


    void resetOriginalColor();
    void setOriginalColor(QColor value);

    bool getHasChessPiece();
    void setHasChessPiece(bool value,ChessPiece *piece = nullptr);

    void checkForCheck();

    Couleur getChessPieceColor() ;
    void setChessPieceColor(Couleur value);

    char rowLoc;
    char colLoc;

    ChessPiece * currentPiece;

private:
    Game *game;
    int taille;
    QBrush brush;
    QColor originalColor;
    bool hasChessPiece;
    Couleur chessPieceColor;


};

#endif // boite_H
