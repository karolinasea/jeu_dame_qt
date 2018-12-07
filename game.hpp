#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSignalMapper>
#include "chessboard.hpp"
#include "button.hpp"
//#include "chesspiece.hpp"
class ChessBoard;
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



    ChessBox *collection[144];
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
    ChessBoard *chess;
    QGraphicsPixmapItem *p;
    QGraphicsPixmapItem *p1;
    Button * playButton;
    Button * playComputerButton;
    Button * size8;
    Button * size10;
    Button * size12;

    QGraphicsTextItem * turnDisplay;


};

#endif // GAME_H
