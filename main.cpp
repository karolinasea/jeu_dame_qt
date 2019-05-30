#include <QApplication>
#include "game.h"

Game *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game = new Game();
    game->showMaximized(); //showMaximized Shows the widget maximized.
    game->displayMainMenu();
    return a.exec();
}



