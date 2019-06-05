#ifndef GAME_H
#define GAME_H
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSignalMapper>
#include <QVector>
#include <QPushButton>
#include "damier.h"
#include "pion.h"
#include "bouton.h"

class Damier;
class Game:public QGraphicsView
{
    Q_OBJECT
public:
    //Constructors
    Game(QWidget *parent = nullptr);
    Game(qreal x, qreal y, qreal width, qreal height, QObject *parent = nullptr);

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

    Couleur getTurn();
    int getNbCases();
    void setTurn( Couleur value);
    void changeTurn();

    char largeurBoite; // public pour le moment pour Damier

    char nbCases;

    //Boite *collection[144];
    QVector<Boite *> tab_damier; //vecteur c mieux, au moins 64 cases réservées (damier 8*8) dans le constructeur

    //QGraphicsTextItem *check;
    QGraphicsTextItem * gameIsOver;
    QList <Pion *> alivePiece;

    void displayMainMenu();

    /*void gameOver();
    void removeAll();*/

public slots:
    void displaySizeMenu();
    void start(int param);
    void resetDamier();


private:
    QGraphicsScene *gameScene;
    QList <Pion *> blancMort;
    QList <Pion *> noirMort;
    QGraphicsRectItem * cimetiere;
    Couleur tour;
    Damier *leDamier;
    //QGraphicsPixmapItem *p;
    //QGraphicsPixmapItem *p1;
    Bouton * playbouton;
    Bouton * playComputerbouton;
    Bouton * size8;
    Bouton * size10;
    //Bouton * size12;
    Bouton * retour;

    QGraphicsTextItem * affTour;
    QGraphicsTextItem * title;


};

#endif // GAME_H
