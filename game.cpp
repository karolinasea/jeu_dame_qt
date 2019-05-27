#include "game.h"
#include "damier.h"

#include <QPixmap>
#include <QDebug>

Game::Game(QWidget *parent ):QGraphicsView(parent)//, tab_damier(144)
{
    /*the QGraphicsView class provides a widget for displaying the contents of a QGraphicsScene*/

    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0, 0, 1400, 1030); //scrollable area
    /* setSceneRect = The scene rectangle defines the extent of the scene. It is primarily used by
    QGraphicsView to determine the view's default scrollable area, and by QGraphicsScene
    to manage item indexing.*/

    //Making the view
    setFixedSize(1400, 900);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    pieceToMove = nullptr; //pieceToMove est un attribut de Game de type Pion

    //display turn on the top middle of the screen
    affTour = new QGraphicsTextItem();
    affTour->setPos(width()/2-100, 10);
    affTour->setZValue(1);
    affTour->setDefaultTextColor(Qt::white);
    affTour->setFont(QFont("", 20));
    affTour->setPlainText("Tour : Blanc");

    //display title in the main menu and the size menu
    title = new QGraphicsTextItem();
    int xPos = 545;
    int yPos = 150;
    title->setPos(xPos,yPos);
    title->setDefaultTextColor(Qt::white);
    title->setFont(QFont("", 50));
    title->setPlainText("Jeu de Dames");

    //display Check
    /*The QGraphicsTextItem class provides a text item that you can add to a QGraphicsScene to display formatted text.*/
    check = new QGraphicsTextItem();
    check->setPos(width()/2+20,10);
    /*Sets the Z-value of the item to z. The Z value decides the stacking order of sibling (neighboring) items.
     A sibling item of high Z value will always be drawn on top of another sibling item with a lower Z value.*/
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("", 20));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn(Couleur::Blanc);

    /*retour = new QGraphicsTextItem();
    retour->setPos(345, 10);
    retour->setPlainText("Retour");
    retour->setDefaultTextColor(Qt::white);*/

    retour = new Bouton("Reinitialiser");
    retour->setPos(300, 5);
    //retour->setRect(0, 0, 150, 30);

    QObject::connect(retour, SIGNAL(clicked()) , this, SLOT(resetDamier()));

}

void Game::resetDamier()
{
    qDebug()<<"resetDamier";
    int r, c;
    if(nbCases==8)
    {
        qDebug()<<"resetDamier 1";
        for(r=0; r<nbCases-1; r++)
            qDebug()<<"resetDamier 2";
        {
            for(c=1; c<nbCases; c+=2)
            {
                qDebug()<<"resetDamier 3";
                Boite *box = tab_damier[r*nbCases+c];
                box->setHasPion(false);
                box->setPionCouleur(Couleur::None);
                //box->currentPiece = nullptr;
            }
        }
    }
    if(nbCases==10)
    {
        qDebug()<<"resetDamier 4";
        Boite *box = tab_damier[0*nbCases+c];
        box->setHasPion(false);
        box->setPionCouleur(Couleur::None);
        box->currentPiece = nullptr;
    }
}

void Game::displayDeadWhite()
{
    int SHIFT=70;
    int j = 0;
    int k = 0;                 // Qlist.size quel type ça renvoie
    for(unsigned int i = 0,n = blancMort.size(); i<n; i++) {
            if(j == 3){
                k++;
                j = 0;
            }
            blancMort[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 70;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = noirMort.size(); i<n; i++) {
        if(j == 3){
            k++;
            j = 0;
        }
        noirMort[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::placeInDeadPlace(Pion *piece)
{
    if(piece->getSide() == Couleur::Blanc) {
        blancMort.append(piece);
        /*King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("Black Won");
            gameOver();
        }*/
        displayDeadWhite();
    }
    else{
        noirMort.append(piece);
        /*King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("White Won");
            gameOver();
        }*/
        displayDeadBlack();
    }
    alivePiece.removeAll(piece);
}

void Game::addToScene(QGraphicsItem *item)
{
    gameScene->addItem(item);
}

void Game::removeFromScene(QGraphicsItem *item)
{
    gameScene->removeItem(item);

}

Couleur Game::getTurn()
{
    return tour;
}

int Game::getNbCases()
{
    return nbCases;
}

void Game::setTurn(Couleur value)
{
    tour = value;
}

void Game::changeTurn()
{
    if(getTurn() == Couleur::Blanc){
        setTurn(Couleur::Noir);
        affTour->setPlainText("Tour : NOIR");
    }
    else {
        setTurn(Couleur::Blanc);
     affTour->setPlainText("Tour : BLANC");
    }
}

void Game::start(int param)
{
        removeFromScene(p);
        //removeFromScene(p1);
        removeFromScene(size8);
        removeFromScene(size10);
        //removeFromScene(size12);
        removeFromScene(title);

        addToScene(retour);

        drawDeadHolder(0,0,Qt::lightGray);
        drawDeadHolder(1100,0,Qt::lightGray);

        nbCases=param;

        if (param==8)
        {
            largeurBoite = 100;
        }
        else if (param==10)
        {
            largeurBoite=80;
        }
        /*else if (param==12)
            largeurBoite=67;*/

        leDamier = new Damier(this, param);
        leDamier->drawBoites(width()/2-400,50);

    addToScene(affTour);

    QGraphicsTextItem* whitePiece = new QGraphicsTextItem();
    whitePiece->setPos(70,10);
    whitePiece->setZValue(1);
    whitePiece->setDefaultTextColor(Qt::white);
    whitePiece->setFont(QFont("",15));
    whitePiece->setPlainText("WHITE PIECE");
    addToScene(whitePiece);

    QGraphicsTextItem *blackPiece = new QGraphicsTextItem();
    blackPiece->setPos(1170,10);
    blackPiece->setZValue(1);
    blackPiece->setDefaultTextColor(Qt::black);
    blackPiece->setFont(QFont("",15));
    blackPiece->setPlainText("BLACK PIECE");
    addToScene(blackPiece);
    addToScene(check);
    leDamier->addPion();

    //run generateur de coup here at first or just let select the avt dt avt gauche
    //gene = new generateur();
    //gene.remplirListes(nbCases);
}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    cimetiere = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    cimetiere->setBrush(brush);
    addToScene(cimetiere);
}

void Game::displaySizeMenu()
{
    removeFromScene(playbouton);
    //removeFromScene(playComputerbouton);

    size8 = new Bouton("64 cases 8x8");
    int pxPos = width()/2 - size8->boundingRect().width()/2;
    size8->setPos(pxPos,300);
    addToScene(size8);

    size10 = new Bouton("100 cases 10x10");
    size10->setPos(pxPos,400);
    addToScene(size10);

    /*size12 = new Bouton("144 cases 12x12");
    size12->setPos(pxPos,500);
    addToScene(size12);*/

    connect(size8,  &Bouton::clicked, this, [this]{ start(8); });
    connect(size10,  &Bouton::clicked, this, [this]{ start(10); });
    //connect(size12, &Bouton::clicked, this, [this]{ start(12); });

}

void Game::displayMainMenu()
{
    /*p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap("pawn.png"));
    p->setPos(420,170);
    addToScene(p);
    p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap("pawn1.png"));
    p1->setPos(920,170);
    addToScene(p1);*/

    addToScene(title);

    //create bouton
    playbouton = new Bouton("Play 2 v 2");
    int pxPos = width()/2 - playbouton->boundingRect().width()/2;
    int pyPos = 300;
    playbouton->setPos(pxPos,pyPos);
    connect(playbouton, SIGNAL(clicked()) , this, SLOT(displaySizeMenu()));
    addToScene(playbouton);

    /*playComputerbouton = new Bouton("Play vs Computer");
    int qxPos = width()/2 - playComputerbouton->boundingRect().width()/2;
    int qyPos = 375;
    playComputerbouton->setPos(qxPos,qyPos);
    //connect(playComputerbouton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(playComputerbouton);*/
}

void Game::gameOver()
{
    //removeAll();
    setTurn(Couleur::Blanc);
    alivePiece.clear();
    leDamier->reset();

}


// pas utilisé
void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}

