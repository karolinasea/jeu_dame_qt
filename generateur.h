#ifndef GENERATEUR_HPP
#define GENERATEUR_HPP

#include <QVector>
//#include "listecoups.hpp"
#include "boite.h"
//#include "game.h"

class Pion;
class listeCoups;
class generateur
{
public:
    generateur(char taille, char row, char col, QVector<Boite *> position, Couleur side, bool dame);
    void remplirListes();
    char chemPlusCourt(char i, char row, char col, char nope);
    void boxSetting(Boite *box);
    void decolor();
    char chemPlusCourtDame(char i, char row, char col, char nope);
    void remplirListesDames();

    Couleur side;
    QVector<Boite *> liste_avant_g;
    QVector<Boite *> liste_avant_d;
    QVector<Boite *> liste_arr_g;
    QVector<Boite *> liste_arr_d;
    QVector<Boite *> liste_avant_g_enn;
    QVector<Boite *> liste_avant_d_enn;
    QVector<Boite *> liste_arr_g_enn;
    QVector<Boite *> liste_arr_d_enn;

    char taille;
    char row;
    char col;
    bool dame=false;
    QVector<Boite *> position;
    QVector<Boite *> liste_enn;
    QVector<Boite *> liste;
    QVector<Boite *> liste_1;
    QVector<Boite *> liste_enn1;
    QVector<Boite *> liste_2;
    QVector<Boite *> liste_enn2;
    QVector<Boite *> liste_3;
    QVector<Boite *> liste_enn3;
    QVector<Boite *> liste_4;
    QVector<Boite *> liste_enn4;
    QVector<Boite *> chem_1;
    QVector<Boite *> chem_enn1;
};

#endif // GENERATEUR_HPP
