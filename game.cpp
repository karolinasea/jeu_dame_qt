#include "game.hpp"

#include <QPixmap>
#include <QDebug>
Game::Game(QWidget *parent ):QGraphicsView(parent)
{

    //Making the Scene
    gameScene = new QGraphicsScene();
    gameScene->setSceneRect(0,0,1400,900);

    //Making the view
    setFixedSize(1400,900);
    //setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setScene(gameScene);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBackgroundBrush(brush);
    pieceToMove = nullptr;

    //display turn
    turnDisplay = new QGraphicsTextItem();
    turnDisplay->setPos(width()/2-100,10);
    turnDisplay->setZValue(1);
    turnDisplay->setDefaultTextColor(Qt::white);
    turnDisplay->setFont(QFont("",18));
    turnDisplay->setPlainText("Tour : Blanc");

    //display Check
    check = new QGraphicsTextItem();
    check->setPos(width()/2-100,860);
    check->setZValue(4);
    check->setDefaultTextColor(Qt::red);
    check->setFont(QFont("",18));
    check->setPlainText("CHECK!");
    check->setVisible(false);
    setTurn(Couleur::Blanc);

}


void Game::displayDeadWhite()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;                 // Qlist.size quel type ça renvoie
    for(unsigned int i = 0,n = whiteDead.size(); i<n; i++) {
            if(j == 4){
                k++;
                j = 0;
            }
            whiteDead[i]->setPos(40+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::displayDeadBlack()
{
    int SHIFT = 50;
    int j = 0;
    int k = 0;
    for(size_t i = 0,n = blackDead.size(); i<n; i++) {
        if(j == 4){
            k++;
            j = 0;
        }
        blackDead[i]->setPos(1140+SHIFT*j++,100+SHIFT*2*k);
    }
}

void Game::placeInDeadPlace(ChessPiece *piece)
{
    if(piece->getSide() == Couleur::Blanc) {
        whiteDead.append(piece);
        /*King *g = dynamic_cast <King *>(piece);
        if(g){

            check->setPlainText("Black Won");
            gameOver();
        }*/
        displayDeadWhite();
    }
    else{
        blackDead.append(piece);
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
    return turn;
}

void Game::setTurn(Couleur value)
{
    turn = value;
}

void Game::changeTurn()
{
    if(getTurn() == Couleur::Blanc){
        setTurn(Couleur::Noir);
        turnDisplay->setPlainText("Tour : NOIR");
    }
    else {
        setTurn(Couleur::Blanc);
     turnDisplay->setPlainText("Tour : BLANC");
    }
}

void Game::start(int param)
{

        removeFromScene(p);
        removeFromScene(p1);
        removeFromScene(size8);
        removeFromScene(size10);
        removeFromScene(size12);

        drawDeadHolder(0,0,Qt::lightGray);
        drawDeadHolder(1100,0,Qt::lightGray);

        chess = new ChessBoard(this, param);
        chess->drawBoxes(width()/2-400,50);

    addToScene(turnDisplay);
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
    chess->addChessPiece();
}

void Game::drawDeadHolder(int x, int y,QColor color)
{
    deadHolder = new QGraphicsRectItem(x,y,300,900);
    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(color);
    deadHolder->setBrush(brush);
    addToScene(deadHolder);
}

void Game::displaySizeMenu()
{
    removeFromScene(playButton);
    removeFromScene(playComputerButton);

    size8 = new Button("64 cases 8x8");
    int pxPos = width()/2 - size8->boundingRect().width()/2;
    size8->setPos(pxPos,300);    
    addToScene(size8);

    size10 = new Button("100 cases 10x10");
    size10->setPos(pxPos,400);
    addToScene(size10);

    size12 = new Button("144 cases 12x12");
    size12->setPos(pxPos,500);
    addToScene(size12);


    connect(size8,  &Button::clicked, this, [this]{ start(8); });
    connect(size10,  &Button::clicked, this, [this]{ start(10); });
    connect(size12, &Button::clicked, this, [this]{ start(12); });


}

void Game::displayMainMenu()
{
    p = new QGraphicsPixmapItem();
    p->setPixmap(QPixmap(":/images/pawn.png"));
    p->setPos(420,170);
    addToScene(p);


    p1 = new QGraphicsPixmapItem();
    p1->setPixmap(QPixmap(":/images/pawn1.png"));
    p1->setPos(920,170);
    addToScene(p1);


    //Create the title
    /*QGraphicsTextItem *titleText = new QGraphicsTextItem("Checkers");
    QFont titleFont("arial" , 60);
    titleText->setFont( titleFont);
    int xPos = width()/2 - titleText->boundingRect().width()/2;
    int yPos = 150;
    titleText->setPos(xPos,yPos);
    addToScene(titleText);
    listG.append(titleText);*/

    //create Button
    playButton = new Button("Play 2 v 2");
    int pxPos = width()/2 - playButton->boundingRect().width()/2;
    int pyPos = 300;
    playButton->setPos(pxPos,pyPos);
    connect(playButton,SIGNAL(clicked()) , this , SLOT(displaySizeMenu()));
    addToScene(playButton);


    playComputerButton = new Button("Play vs Computer");
    int qxPos = width()/2 - playComputerButton->boundingRect().width()/2;
    int qyPos = 375;
    playComputerButton->setPos(qxPos,qyPos);
    //connect(playComputerButton, SIGNAL(clicked()),this,SLOT(close()));
    addToScene(playComputerButton);

}

void Game::gameOver()
{
    //removeAll();
    setTurn(Couleur::Blanc);
    alivePiece.clear();
    chess->reset();




}


// pas utilisé
void Game::removeAll(){
    QList<QGraphicsItem*> itemsList = gameScene->items();
    for(size_t i = 0, n = itemsList.size();i<n;i++) {
        if(itemsList[i]!=check)
          removeFromScene(itemsList[i]);
    }
}
