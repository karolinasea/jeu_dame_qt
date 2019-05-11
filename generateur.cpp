#include "generateur.hpp"
#include <QDebug>
generateur::generateur(char taille,char row, char col,QVector<Boite *> position,Couleur side):
    taille(taille),row(row),col(col),position(position),side(side)
{
}
void generateur::decolor(){  // UTILE  ??
    for(char i = 0, n = position.size(); i < n;i++) {
         position[i]->resetOriginalColor();
    }
}
void generateur::boxSetting(Boite *box){
        box->setCouleur(Qt::darkRed);
}

char generateur::chemPlusCourt(char i, char row, char col, char nope){
    char a=0,b=0,c=0,d=0;
    qDebug()<<"dans chem plus court row="<<(int)row<<(int)col<<"i="<<(int)i;
    if (nope!=1){ //nope ==1 veut dire on vient de arr droite, pour pas retourner en arr
    // qqch a manger en avant gauche ?
    if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc) {
        if(!position[(row+2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col-2])) {// on verifie ya pas de pion sur point de chute
            qDebug()<<"avant gauche";
            liste.append(position[(row+2)*taille+col-2]);
            liste_enn.append(position[(row+1)*taille+col-1]);
            a=chemPlusCourt(i+1,row+2,col-2,4);
            //boxSetting(position[(row+2)*taille+col-2]);
                qDebug()<<"a="<<(int)a;
        }
    }}
    if (a>i) i=a;
    if (nope!=2){
    // qqch a manger en avant droite ?
    if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc) {
        if(!position[(row+2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col+2])) {// on verifie ya pas de pion sur point de chute
            qDebug()<<"avant droite";
            liste_enn.append(position[(row+1)*taille+col+1]);
             liste.append(position[(row+2)*taille+col+2]);
            b=chemPlusCourt(i+1,row+2,col+2,3);
            //boxSetting(position[(row+2)*taille+col+2]);
            qDebug()<<"b="<<(int)b;
        }
    }}
    if (b>i) i=b;
    if (nope!=3){
    // qqch a manger en gauche arriere ?
    if(col > 1 && row >1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc) {
        if(!position[(row-2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col-2])) { // on verifie ya pas de pion sur point de chute
            qDebug()<<"gauche arriere";
            liste.append(position[(row-2)*taille+col-2]);
            liste_enn.append(position[(row-1)*taille+col-1]);
            c=chemPlusCourt(i+1,row-2,col-2,2);
            //boxSetting(position[(row-2)*taille+col-2]);
            qDebug()<<"c="<<(int)c;
        }
    }}
    if (c>i) i=c;
    if (nope!=4){
    // qqch a manger a droite arriere ?
    if(col <taille-2 && row >1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc) {
        if(!position[(row-2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col+2])) { // on verifie ya pas de pion sur point de chute
            qDebug()<<"droite arriere";
                liste_enn.append(position[(row-1)*taille+col+1]);
                liste.append(position[(row-2)*taille+col+2]);
            d=chemPlusCourt(i+1,row-2,col+2,1);
            //boxSetting(position[(row-2)*taille+col+2]);
            qDebug()<<"d="<<(int)d;
        }
    }}
    if (d>i) i=d;
    /*t1 = (a > b? a : b);
    t2 = (c > d? c : d);
    i = (t1 > t2? t1 : t2);*/

return i;
}

void generateur::remplirListes()
{
    liste_avant_g.clear();
    liste_avant_d.clear();
    liste_arr_g.clear();
    liste_arr_d.clear();

    liste_enn.clear();
    liste.clear();
    //boitePionEnnemi.clear();

    //qDebug()<<row<<" "<<col;
char a=0,b=0,c=0,d=0;
    //POur les pions noirs de l'ordi
    if (this->side==Couleur::Noir){
        // qqch a manger en avant gauche ?
        if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc) {

            if(!position[(row+2)*taille+col-2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
            liste_avant_g.append(position[(row+2)*taille+col-2]);
            liste_avant_g_enn.append(position[(row+1)*taille+col-1]);
            //boxSetting(location.last());
                a=chemPlusCourt(1,row+2,col-2,4);
            }
        }
        liste_avant_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_g.append(liste);
        liste.clear();
        // qqch a manger en avant droite ?
        if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc) {
            if(!position[(row+2)*taille+col+2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
               liste_avant_d_enn.append(position[(row+1)*taille+col+1]);
                liste_avant_d.append(position[(row+2)*taille+col+2]);
                //boxSetting(location.last());
                b=chemPlusCourt(1,row+2,col+2,3);
            }
        }
        liste_avant_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_d.append(liste);
        liste.clear();
        // qqch a manger en gauche arriere ?
        if(col > 1 && row >1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc) {
            if(!position[(row-2)*taille+col-2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_arr_g.append(position[(row-2)*taille+col-2]);
                liste_arr_g_enn.append(position[(row-1)*taille+col-1]);
                //boxSetting(location.last());
                c=chemPlusCourt(1,row-2,col-2,2);
            }
        }
        liste_arr_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_g.append(liste);
        liste.clear();
        // qqch a manger a droite arriere ?
        if(col <taille-2 && row >1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc) {
            if(!position[(row-2)*taille+col+2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_arr_d_enn.append(position[(row-1)*taille+col+1]);
                liste_arr_d.append(position[(row-2)*taille+col+2]);
                //boxSetting(location.last());
                d=chemPlusCourt(1,row-2,col+2,1);
            }
        }
        liste_arr_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_d.append(liste);
        liste.clear();

        if(row< taille-1 && col>0 && (!position[(row+1)*taille+col-1]->getHasPion())) { //gauche juste avancer
            //location.append(position[(row+1)*taille+col-1]);
            //boitePionEnnemi.append(nullptr);
            //boxSetting(location.last());
            liste_avant_g.append(position[(row+1)*taille+col-1]);
        }

        if(row< taille-1 && col<taille-1 && (!position[(row+1)*taille+col+1]->getHasPion())) { //droite juste avancer
            //location.append(position[(row+1)*taille+col+1]);
            //boitePionEnnemi.append(nullptr);
            //boxSetting(location.last());
            liste_avant_d.append(position[(row+1)*taille+col+1]);
        }
      }

    else{

        if(col > 1 && row > 1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Noir) {  // qqch a manger a gauche ?
            if(!position[(row-2)*taille+col-2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_avant_g.append(position[(row-2)*taille+col-2]);
                liste_avant_g_enn.append(position[(row-1)*taille+col-1]);
                //boxSetting(location.last());
                    a=chemPlusCourt(1,row-2,col-2,4);
            }
        }
        liste_avant_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_g.append(liste);
        liste.clear();
        if(col < taille-2 && row > 1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Noir) { //qqch a manger a droite ?
            if(!position[(row-2)*taille+col+2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_avant_d.append(position[(row-2)*taille+col+2]);
                liste_avant_d_enn.append(position[(row-1)*taille+col+1]);
                //boxSetting(location.last());
                    a=chemPlusCourt(1,row-2,col+2,3);
            }
        }
        liste_avant_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_d.append(liste);
        liste.clear();
        if(row>0 && col < taille-1 && (!position[(row-1)*taille+col+1]->getHasPion())) { //droite
            liste_avant_d.append(position[(row-1)*taille+col+1]);



        }
        if(col>0 && row >0 && (!position[(row-1)*taille+col-1]->getHasPion())) { // gauche
            liste_avant_g.append(position[(row-1)*taille+col-1]);


        }
        if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Noir) {  // qqch a manger a gauche arriere ?
            if(!position[(row+2)*taille+col-2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_arr_g.append(position[(row+2)*taille+col-2]);
                liste_arr_g_enn.append(position[(row+1)*taille+col-1]);
                //boxSetting(location.last());
                    a=chemPlusCourt(1,row+2,col-2,2);
            }
        }
        liste_arr_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_g.append(liste);
        liste.clear();
        if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Noir) {  // qqch a manger a droite arriere ?
            if(!position[(row+2)*taille+col+2]->getHasPion()) { // on verifie ya pas de pion sur point de chute
                liste_arr_d.append(position[(row+2)*taille+col+2]);
                liste_arr_d_enn.append(position[(row+1)*taille+col+1]);
                //boxSetting(location.last());
                    a=chemPlusCourt(1,row+2,col+2,1);
            }
        }
        liste_arr_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_d.append(liste);
        liste.clear();
    }

        qDebug()<<"a= "<<(int)a<<"  b= "<<(int)b<<"  c= "<<(int)c<<"  d= "<<(int)d;
        for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
             liste_arr_d[i]->setCouleur(Qt::blue);
        for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
             liste_arr_g[i]->setCouleur(Qt::green);
        for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
             liste_avant_d[i]->setCouleur(Qt::yellow);
        for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
             liste_avant_g[i]->setCouleur(Qt::red);
}
