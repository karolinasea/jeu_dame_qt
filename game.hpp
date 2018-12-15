#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSignalMapper>
#include "damier.hpp"
#include "bouton.hpp"
#include "pion.hpp"
class Damier;
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
    void placeInDeadPlace(Pion *piece);

    //Scene Related
    void addToScene(QGraphicsItem *item);
    void removeFromScene(QGraphicsItem *item);

    //getters/setters
    Pion *pieceToMove;

    Couleur getTurn() ;
    void setTurn( Couleur value);
    void changeTurn();

    char largeurBoite; // public pour le moment pour Damier

    Boite *collection[144];
    QGraphicsTextItem *check;

    QList <Pion *> alivePiece;
    void displayMainMenu();


    void gameOver();
    void removeAll();
public slots:
    void displaySizeMenu();
    void start(int param);
private:
        QGraphicsScene *gameScene;
    QList <Pion *> blancMort;
    QList <Pion *> noirMort;
    QGraphicsRectItem * cimetiere;
    Couleur tour;
    Damier *leDamier;
    QGraphicsPixmapItem *p;
    QGraphicsPixmapItem *p1;
    Bouton * playbouton;
    Bouton * playComputerbouton;
    Bouton * size8;
    Bouton * size10;
    Bouton * size12;

    QGraphicsTextItem * affTour;


};

#endif // GAME_H
