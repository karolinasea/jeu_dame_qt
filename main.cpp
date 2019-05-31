#include <QApplication>
#include "game.h"

Game *game;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    int result;
    do {

        game = new Game();
        game->showMaximized(); //showMaximized Shows the widget maximized.
        game->displayMainMenu();
        result= a.exec();
        game->hide();
    } while(result==2000);
    return result;

}



