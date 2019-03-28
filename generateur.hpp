#ifndef GENERATEUR_HPP
#define GENERATEUR_HPP

#include <QVector>
#include "listecoups.hpp"
#include "boite.hpp"
class Pion;
class listeCoups;
class generateur
{
public:
    generateur(char taille,char row, char col,QVector<Boite *> position, Couleur side );
    void remplirListes();
    char chemPlusCourt(char i, char row, char col, char nope);
void boxSetting(Boite *box);
void decolor();

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
    QVector<Boite *> position;
    QVector<Boite *> liste_enn;
    QVector<Boite *> liste;
};

#endif // GENERATEUR_HPP
