#ifndef LISTECOUPS_H
#define LISTECOUPS_H

#include "pion.h"
#include "boite.h"
class listeCoups
{
public:
    listeCoups();
    void vider();
    void ajouter(Boite *);
    Boite * suivant();
    void reset();

private:
    QList <Boite *> listeC;
    unsigned int taille;
    unsigned int indice;
};

#endif // LISTECOUPS_H
