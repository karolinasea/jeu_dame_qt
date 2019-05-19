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
void generateur::boxSetting(Boite *box)
{
        box->setCouleur(Qt::darkRed);
}

char generateur::chemPlusCourt(char i, char row, char col, char nope) //what is nope????
{
    char a=0, b=0, c=0, d=0 /*,t1,t2*/;

    //qDebug pour afficher msg dans console
    //qDebug()<<"dans chem plus court row="<<(int)row<<"col= "<<(int)col<<"i="<<(int)i<<"nope= "<<(int)nope;
    //position et liste sont des list(QVector) contenant des objects de type Boite
    if (nope!=1)
    {
        qDebug()<<"dans if nope!=1";
        // qqch a manger en avant gauche ?
        //if pion blanc and inside board?
        if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
        {
            qDebug()<<"dans if nope!=1 et dans le 2eme if donc qqch manger avt gch";
            //si la case/Boite en avt gch n est pas contenue dans la liste liste et dans la liste position
            /* contains(qqch) = Returns true if the list contains an occurrence of value; otherwise returns false.*/
            // on verifie ya pas de pion sur point de chute
            if(!position[(row+2)*taille+col-2]->getHasPion() && !liste.contains(position[(row+2)*taille+col-2]))
            {
                liste.append(position[(row+2)*taille+col-2]);
                liste_enn.append(position[(row+1)*taille+col-1]);
                a = chemPlusCourt(i+1,row+2,col-2,4); //recursive
                //boxSetting(position[(row+2)*taille+col-2]);
                qDebug()<<"a="<<(int)a;
            }
        }
    }

    if (a>i) i=a;

    if (nope!=2)
    {
        // qqch a manger en avant droite ?
        if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            // on verifie ya pas de pion sur point de chute
            if(!position[(row+2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col+2]))
            {
                qDebug()<<"avant droite";
                liste_enn.append(position[(row+1)*taille+col+1]);
                 liste.append(position[(row+2)*taille+col+2]);
                b = chemPlusCourt(i+1,row+2,col+2,3);
                //boxSetting(position[(row+2)*taille+col+2]);
                qDebug()<<"b="<<(int)b;
            }
        }
    }

    if (b>i) i=b;

    if (nope!=3)
    {
        // qqch a manger en gauche arriere ?
        if(col > 1 && row >1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
        {
            if(!position[(row-2)*taille+col-2]->getHasPion() && !liste.contains(position[(row-2)*taille+col-2]))
            {
                qDebug()<<"gauche arriere";
                liste.append(position[(row-2)*taille+col-2]);
                liste_enn.append(position[(row-1)*taille+col-1]);
                c = chemPlusCourt(i+1,row-2,col-2,2);
                //boxSetting(position[(row-2)*taille+col-2]);
                qDebug()<<"c="<<(int)c;
            }
        }
    }

    if (c>i) i=c;

    if (nope!=4)
    {
        // qqch a manger a droite arriere ?
        if(col <taille-2 && row >1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            // on verifie ya pas de pion sur point de chute
            if(!position[(row-2)*taille+col+2]->getHasPion() && !liste.contains(position[(row-2)*taille+col+2]))
            {
                qDebug()<<"droite arriere";
                liste_enn.append(position[(row-1)*taille+col+1]);
                liste.append(position[(row-2)*taille+col+2]);
                d=chemPlusCourt(i+1,row-2,col+2,1);
                //boxSetting(position[(row-2)*taille+col+2]);
                qDebug()<<"d="<<(int)d;
            }
        }
    }

    if (d>i) i=d;

    /*t1 = (a > b? a : b);
    t2 = (c > d? c : d);
    i = (t1 > t2? t1 : t2);*/

//qDebug()<<"fin de la fonction chemPlusCourt returns i ="<<(int)i;

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

    qDebug()<<"start remplirListes method";

    char a=0, b=0, c=0, d=0;

    //Pour les pions noirs de l'ordi
    if (this->side==Couleur::Noir)
    {
        // qqch a manger en avant gauche ?
        if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc) {

            if(!position[(row+2)*taille+col-2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_avant_g.append(position[(row+2)*taille+col-2]);
                liste_avant_g_enn.append(position[(row+1)*taille+col-1]);
                //boxSetting(location.last());
                a = chemPlusCourt(1,row+2,col-2,4);
            }
        }

        liste_avant_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_g.append(liste);
        liste.clear();

        // qqch a manger en avant droite ?
        if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            if(!position[(row+2)*taille+col+2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_avant_d_enn.append(position[(row+1)*taille+col+1]);
                liste_avant_d.append(position[(row+2)*taille+col+2]);
                //boxSetting(location.last());
                b = chemPlusCourt(1,row+2,col+2,3);
            }
        }

        liste_avant_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_d.append(liste);
        liste.clear();

        // qqch a manger en gauche arriere ?
        if(col > 1 && row >1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
        {
            if(!position[(row-2)*taille+col-2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_arr_g.append(position[(row-2)*taille+col-2]);
                liste_arr_g_enn.append(position[(row-1)*taille+col-1]);
                //boxSetting(location.last());
                c = chemPlusCourt(1,row-2,col-2,2);
            }
        }

        liste_arr_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_g.append(liste);
        liste.clear();

        // qqch a manger a droite arriere ?
        if(col <taille-2 && row >1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
        {
            if(!position[(row-2)*taille+col+2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_arr_d_enn.append(position[(row-1)*taille+col+1]);
                liste_arr_d.append(position[(row-2)*taille+col+2]);
                //boxSetting(location.last());
                d = chemPlusCourt(1,row-2,col+2,1);
            }
        }

        liste_arr_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_d.append(liste);
        liste.clear();

        //ce if empeche les pions qui peuvent manger un/pls pions ennemis d'avancer sur une autre cases (oblige a manger) :)
        if(liste_avant_d.size()==0 && liste_avant_g.size()==0 && liste_arr_g.size()==0 && liste_arr_d.size()==0)
        {
            if(row< taille-1 && col>0 && (!position[(row+1)*taille+col-1]->getHasPion()))
            { //gauche juste avancer
                //location.append(position[(row+1)*taille+col-1]);
                //boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());
                liste_avant_g.append(position[(row+1)*taille+col-1]);
            }

            if(row< taille-1 && col<taille-1 && (!position[(row+1)*taille+col+1]->getHasPion()))
            { //droite juste avancer
                //location.append(position[(row+1)*taille+col+1]);
                //boitePionEnnemi.append(nullptr);
                //boxSetting(location.last());
                liste_avant_d.append(position[(row+1)*taille+col+1]);
            }
        }
      }

    else //pour les pions blancs
    {
        qDebug()<<"remplirListes method pour les pions blancs";
        if(col > 1 && row > 1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
        {  // qqch a manger a gauche ?
            if(!position[(row-2)*taille+col-2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_avant_g.append(position[(row-2)*taille+col-2]);
                liste_avant_g_enn.append(position[(row-1)*taille+col-1]);
                //boxSetting(location.last());
                a = chemPlusCourt(1,row-2,col-2,4);
            }
        }

        liste_avant_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_g.append(liste);
        liste.clear();

        if(col < taille-2 && row > 1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
        { //qqch a manger a droite ?
            if(!position[(row-2)*taille+col+2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_avant_d.append(position[(row-2)*taille+col+2]);
                liste_avant_d_enn.append(position[(row-1)*taille+col+1]);
                //boxSetting(location.last());
                a = chemPlusCourt(1,row-2,col+2,3);
            }
        }

        liste_avant_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_avant_d.append(liste);
        liste.clear();

        if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
        {  // qqch a manger a gauche arriere ?
            if(!position[(row+2)*taille+col-2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_arr_g.append(position[(row+2)*taille+col-2]);
                liste_arr_g_enn.append(position[(row+1)*taille+col-1]);
                //boxSetting(location.last());
                a = chemPlusCourt(1,row+2,col-2,2);
            }
        }

        liste_arr_g_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_g.append(liste);
        liste.clear();

        if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
        {  // qqch a manger a droite arriere ?
            if(!position[(row+2)*taille+col+2]->getHasPion())
            { // on verifie ya pas de pion sur point de chute
                liste_arr_d.append(position[(row+2)*taille+col+2]);
                liste_arr_d_enn.append(position[(row+1)*taille+col+1]);
                //boxSetting(location.last());
                a = chemPlusCourt(1,row+2,col+2,1);
            }
        }

        liste_arr_d_enn.append(liste_enn);
        liste_enn.clear();
        liste_arr_d.append(liste);
        liste.clear();

        //ce if empeche les pions qui peuvent manger un/pls pions ennemis d'avancer sur une autre cases (oblige a manger) :)
        if(liste_avant_d.size()==0 && liste_avant_g.size()==0 && liste_arr_g.size()==0 && liste_arr_d.size()==0)
        {
            if(row>0 && col < taille-1 && (!position[(row-1)*taille+col+1]->getHasPion()))
            { //droite
                 qDebug()<<"remplirListes method possibilite d'avancer a dte";
                liste_avant_d.append(position[(row-1)*taille+col+1]);
            }

            if(col>0 && row >0 && (!position[(row-1)*taille+col-1]->getHasPion()))
            { // gauche
                qDebug()<<"remplirListes method possibilite d'avancer a gch";
                liste_avant_g.append(position[(row-1)*taille+col-1]);
            }
        }
    }

        qDebug()<<"a= "<<(int)a<<"  b= "<<(int)b<<"  c= "<<(int)c<<"  d= "<<(int)d;


        for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
        {
             liste_arr_d[i]->setCouleur(Qt::blue);
        }
        for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
        {
             liste_arr_g[i]->setCouleur(Qt::green);
        }
        for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
        {
             liste_avant_d[i]->setCouleur(Qt::yellow);
        }
        for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
        {
             liste_avant_g[i]->setCouleur(Qt::red);
        }
}
