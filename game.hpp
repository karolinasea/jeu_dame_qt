#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSignalMapper>
#include "damier.hpp"
#include "bouton.hpp"
//#include "chesspiece.hpp"
class damier;
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = nullptr);

    //public Methods
    void drawDeadHolder(int x, int y, QColor color);
    void displayDeadWhite();
    void displayDeadBlack();
    void placeInDeadPlace(ChessPiece *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //getters/setters
    ChessPiece *pieceToMove;

    Couleur getTurn() ;
    void setTurn( Couleur value);
    void changeTurn();



    boite *collection[144];
    QGraphicsTextItem *check;

    QList <ChessPiece *> alivePiece;
    void displayMainMenu();


    void gameOver();
    void removeAll();
public slots:
    void displaySizeMenu();
    void start(int param);
private:
        QGraphicsScene *gameScene;
    QList <ChessPiece *> whiteDead;
    QList <ChessPiece *> blackDead;
    QGraphicsRectItem * deadHolder;
    Couleur turn;
    damier *chess;
    QGraphicsPixmapItem *p;
    QGraphicsPixmapItem *p1;
    bouton * playbouton;
    bouton * playComputerbouton;
    bouton * size8;
    bouton * size10;
    bouton * size12;

    QGraphicsTextItem * turnDisplay;


};

#endif // GAME_H
