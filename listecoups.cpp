#include "listecoups.h"

listeCoups::listeCoups()
{
    this->taille=0;
    this->indice=0;
}

void listeCoups::vider(){
    this->listeC.clear();
    this->taille=0;
    this->indice=0;
}

void listeCoups::ajouter(Boite * b){
    this->listeC.append(b);
    taille++;
}
void listeCoups::reset(){
    indice=0;
}
