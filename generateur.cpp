#include "generateur.h"
#include "game.h"
#include "pion.h"
#include <QDebug>

generateur::generateur(char taille, char row, char col, QVector<Boite *> position, Couleur side, bool dame):
    taille(taille), row(row), col(col), position(position), side(side), dame(dame)
{

}

void generateur::decolor(){
    for(char i = 0, n = position.size(); i < n;i++) {
         position[i]->resetOriginalColor();
    }
}

char generateur::chemPlusCourt(char i, char row, char col, char nope){

    char a=0,b=0,c=0,d=0;

    /*position et liste sont des list(QVector) contenant des objects de type Boite QVector<Boite *>
    The QVector class is a template class that provides a dynamic array.
    QVector<T> is one of Qt's generic container classes. It stores its items in adjacent memory
    locations and provides fast index-based access.*/

    qDebug()<<"dans chem plus court row="<<(int)row<<"col="<<(int)col<<"i="<<(int)i<<"nope="<<(int)nope<<"a"<<(int)a;

    //nope ==1 veut dire on vient de arr droite, pour pas retourner en arr pour ne pas reverifier en arr droite?
    //pour les pions noirs

    if(side==Couleur::Noir)
    {
        if (nope!=1)
        {
            // qqch a manger en avant gauche ?
            if(col > 1 && row < taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
            {
                if(!position[(row+2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col-2]))
                {
                    qDebug()<<"q1";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"avant gauche";
                    liste.append(position[(row+2)*taille+col-2]);
                    liste_enn.append(position[(row+1)*taille+col-1]);
                    a=chemPlusCourt(i+1,row+2,col-2,4);
                    //boxSetting(position[(row+2)*taille+col-2]);
                    qDebug()<<"a="<<(int)a;
                }
            }
        }

        if (a>i) i=a;

        //nope ==2 veut dire on vient de arr gauche?, pour pas reverifier arr gauche car on ne peut pas retourner en avt dte si on vient de arr gauche (sa ferait un aller-retour)
        if (nope!=2)
        {
            // qqch a manger en avant droite ?
            if(col <taille-2 && row < taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
            {
                if(!position[(row+2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col+2]))
                {
                    qDebug()<<"q2";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"avant droite";
                    liste_enn.append(position[(row+1)*taille+col+1]);
                     liste.append(position[(row+2)*taille+col+2]);
                    b=chemPlusCourt(i+1,row+2,col+2,3);
                    //boxSetting(position[(row+2)*taille+col+2]);
                    qDebug()<<"b="<<(int)b;
                }
            }
        }

        if (b>i) i=b;

        if (nope!=3) //nope==3 on vient de arr gch
        {
            // qqch a manger en gauche arriere ?
            if(col > 1 && row >1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Blanc)
            {
                if(!position[(row-2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col-2]))
                {
                    qDebug()<<"q3";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"gauche arriere";
                    liste.append(position[(row-2)*taille+col-2]);
                    liste_enn.append(position[(row-1)*taille+col-1]);
                    c=chemPlusCourt(i+1,row-2,col-2,2);
                    //boxSetting(position[(row-2)*taille+col-2]);
                    qDebug()<<"c="<<(int)c;
                }
            }
        }

        if (c>i) i=c;

        if (nope!=4) //nope==4 pion vient de avt gauche?
        {
            // qqch a manger a droite arriere ?
            if(col <taille-2 && row >1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Blanc)
            {
                if(!position[(row-2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col+2]))
                {
                    qDebug()<<"q4";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"droite arriere";
                    liste_enn.append(position[(row-1)*taille+col+1]);
                    liste.append(position[(row-2)*taille+col+2]);
                    d=chemPlusCourt(i+1,row-2,col+2,1);
                    //boxSetting(position[(row-2)*taille+col+2]);
                    qDebug()<<"d="<<(int)d;
                }
            }
        }
    }
    else if(side==Couleur::Blanc)
    {
    //pour les pion blancs
        if (nope!=1)
        {
            // qqch a manger en avant gauche ?
            if(col > 1 && row > 1 && position[(row-1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
            {
                qDebug()<<"q101";
                if(!position[(row-2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col-2]))
                {
                    qDebug()<<"q1";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"avant gauche";
                    liste.append(position[(row-2)*taille+col-2]);
                    liste_enn.append(position[(row-1)*taille+col-1]);
                    a=chemPlusCourt(i+1,row-2,col-2,4);
                    //boxSetting(position[(row+2)*taille+col-2]);
                    qDebug()<<"a="<<(int)a;
                }
            }
        }

        if (a>i) i=a;

        //nope ==2 veut dire on vient de arr gauche?, pour pas reverifier arr gauche car on ne peut pas retourner en avt dte si on vient de arr gauche (sa ferait un aller-retour)
        if (nope!=2)
        {
            // qqch a manger en avant droite ?
            if(col <taille-2 && row > 1 && position[(row-1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
            {
                if(!position[(row-2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row-2)*taille+col+2]))
                {
                    qDebug()<<"q2";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"avant droite";
                    liste_enn.append(position[(row-1)*taille+col+1]);
                     liste.append(position[(row-2)*taille+col+2]);
                    b=chemPlusCourt(i+1,row-2,col+2,3);
                    //boxSetting(position[(row+2)*taille+col+2]);
                    qDebug()<<"b="<<(int)b;
                }
            }
        }

        if (b>i) i=b;

        if (nope!=3) //nope==3 on vient de arr gch
        {
            // qqch a manger en gauche arriere ?
            if(col > 1 && row <taille-2 && position[(row+1)*taille+col-1]->getPionCouleur() == Couleur::Noir)
            {
                if(!position[(row+2)*taille+col-2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col-2]))
                {
                    qDebug()<<"q3";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"gauche arriere";
                    liste.append(position[(row+2)*taille+col-2]);
                    liste_enn.append(position[(row+1)*taille+col-1]);
                    c=chemPlusCourt(i+1,row+2,col-2,2);
                    //boxSetting(position[(row-2)*taille+col-2]);
                    qDebug()<<"c="<<(int)c;
                }
            }
        }

        if (c>i) i=c;

        if (nope!=4) //nope==4 pion vient de avt gauche?
        {
            // qqch a manger a droite arriere ?
            if(col <taille-2 && row <taille-2 && position[(row+1)*taille+col+1]->getPionCouleur() == Couleur::Noir)
            {
                if(!position[(row+2)*taille+col+2]->getHasPion()&&!liste.contains(position[(row+2)*taille+col+2]))
                {
                    qDebug()<<"q4";
                    // on verifie ya pas de pion sur point de chute
                    qDebug()<<"droite arriere";
                    liste_enn.append(position[(row+1)*taille+col+1]);
                    liste.append(position[(row+2)*taille+col+2]);
                    d=chemPlusCourt(i+1,row+2,col+2,1);
                    //boxSetting(position[(row-2)*taille+col+2]);
                    qDebug()<<"d="<<(int)d;
                }
            }
        }

        if (d>i) i=d;
}
    /*t1 = (a > b? a : b);
    t2 = (c > d? c : d);
    i = (t1 > t2? t1 : t2);*/

return i;

}

void generateur::remplirListesDames()
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

    //si le pion est noir
    if (side==Couleur::Noir)
    {
        qDebug()<<"remplirListes method pour les pions noirs";
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

    else if(side==Couleur::Blanc) //pour les pions blancs
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
        qDebug()<<"avt d size = "<<liste_avant_d.size();
        qDebug()<<"avt g size = "<<liste_avant_g.size();
        qDebug()<<"arr d size = "<<liste_arr_d.size();
        qDebug()<<"arr g size = "<<liste_arr_g.size();
        qDebug()<<"avt d enn size = "<<liste_avant_d_enn.size();
        qDebug()<<"avt g enn size = "<<liste_avant_g_enn.size();
        qDebug()<<"arr d enn size = "<<liste_arr_d_enn.size();
        qDebug()<<"arr g enn size = "<<liste_arr_g_enn.size();
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

    //si le pion est noir
    if (this->side==Couleur::Noir)
    {
        qDebug()<<"remplirListes method pour les pions noirs";
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

    //si il n'y a pas de pion ennemis a manger et que on peut selement avancer a dt ou a gch ou les deux
    if(liste_arr_d_enn.isEmpty() && liste_avant_d_enn.isEmpty() && liste_arr_g_enn.isEmpty() && liste_avant_g_enn.isEmpty())
    {
        qDebug()<<"NO ENNEMIS";
        for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
        {
             liste_avant_d[i]->setCouleur(Qt::yellow);
        }
        for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
        {
             liste_avant_g[i]->setCouleur(Qt::red);
        }
        for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
        {
             liste_arr_d[i]->setCouleur(Qt::blue);
        }
        for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
        {
             liste_arr_g[i]->setCouleur(Qt::green);
        }
    }
    //si il y a des pions ennemis a manger on regarde quelle liste en a le plus et on affiche seulement celle qui en a le plus
    else if(!liste_arr_d_enn.isEmpty() || !liste_avant_d_enn.isEmpty() || !liste_arr_g_enn.isEmpty() || !liste_avant_g_enn.isEmpty())
    {
        if(liste_avant_d_enn.size()==liste_arr_d_enn.size())
        {
            qDebug()<<"== vd rd";
            for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
            for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                         liste_avant_d[i]->setCouleur(Qt::yellow);
                    }

        }
        else if(liste_avant_d_enn.size()==liste_arr_g_enn.size())
        {
            qDebug()<<"== vd rg";
                    for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
                    {
                         liste_arr_g[i]->setCouleur(Qt::green);
                    }
                    for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                        liste_avant_d[i]->setCouleur(Qt::yellow);
                    }
        }
        else if(liste_avant_d_enn.size()==liste_avant_g_enn.size())
        {
            qDebug()<<"== vd vg";
                    for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                         liste_avant_d[i]->setCouleur(Qt::yellow);
                    }
                    for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::red);
                    }
        }
        else if(liste_avant_g_enn.size()==liste_arr_g_enn.size())
        {
            qDebug()<<"== vg rg";
                    for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
                    {
                         liste_arr_g[i]->setCouleur(Qt::green);
                    }
                    for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::red);
                    }
        }
        else if(liste_avant_g_enn.size()==liste_arr_d_enn.size())
        {
            qDebug()<<"== vg rg";
            for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
                    for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::red);
                    }
        }
        else if(liste_arr_d_enn.size()==liste_arr_g_enn.size())
        {
            qDebug()<<"== rd rg";
                    for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
                    {
                         liste_arr_g[i]->setCouleur(Qt::green);
                    }
                    for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                            {
                                 liste_arr_d[i]->setCouleur(Qt::blue);
                            }
        }
        else if(liste_avant_d_enn.size()==liste_arr_d_enn.size() && liste_avant_d_enn.size()==liste_arr_g_enn.size())
        {
            qDebug()<<"== vd rd";
            for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
            for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                         liste_avant_d[i]->setCouleur(Qt::yellow);
                    }
            for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
            {
                 liste_arr_g[i]->setCouleur(Qt::green);
            }

        }
        else if(liste_avant_d_enn.size()==liste_arr_g_enn.size() && liste_avant_d_enn.size()==liste_avant_g_enn.size())
        {
            qDebug()<<"== vd rg";
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
        else if(liste_avant_d_enn.size()==liste_arr_d_enn.size() && liste_avant_d_enn.size()==liste_avant_g_enn.size())
        {
            qDebug()<<"== vd vg";
                    for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                         liste_avant_d[i]->setCouleur(Qt::yellow);
                    }
                    for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::red);
                    }
                    for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
        }
        else if(liste_avant_g_enn.size()==liste_arr_g_enn.size() && liste_avant_g_enn.size()==liste_arr_d_enn.size())
        {
            qDebug()<<"== vg rg";
                    for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
                    {
                         liste_arr_g[i]->setCouleur(Qt::green);
                    }
                    for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::red);
                    }
                    for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
        }
        else if(liste_avant_g_enn.size()==liste_arr_g_enn.size() && liste_avant_g_enn.size()==liste_arr_d_enn.size() && liste_avant_g_enn.size()==liste_avant_d_enn.size())
        {
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

        QVector<Boite *> mostEaten;
        mostEaten = liste_avant_g_enn;
        int max = mostEaten.size();
        int codeEnn = 0;

        if(liste_avant_d_enn.size()>max)
        {
            mostEaten = liste_avant_d_enn;
            codeEnn=1;
        }
        else if(liste_arr_d_enn.size()>max)
        {
            mostEaten = liste_arr_d_enn;
            codeEnn=2;
        }
        else if(liste_arr_g_enn.size()>max)
        {
            mostEaten = liste_arr_g_enn;
            codeEnn=3;
        }

        if(codeEnn==0)
        {
            qDebug()<<"codeEnn==0";
            for(size_t i = 0, n = liste_avant_g.size(); i < n;i++)
                    {
                         liste_avant_g[i]->setCouleur(Qt::blue);
                    }
        }
        else if(codeEnn==1)
        {
            qDebug()<<"codeEnn==1";
            for(size_t i = 0, n = liste_avant_d.size(); i < n;i++)
                    {
                         liste_avant_d[i]->setCouleur(Qt::blue);
                    }
        }
        else if(codeEnn==2)
        {
            qDebug()<<"codeEnn==2";
            for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
                    {
                         liste_arr_d[i]->setCouleur(Qt::blue);
                    }
        }
        else if(codeEnn==3)
        {
            qDebug()<<"codeEnn==3";
            for(size_t i = 0, n = liste_arr_g.size(); i < n;i++)
                    {
                         liste_arr_g[i]->setCouleur(Qt::blue);
                    }
        }
    }




        /*for(size_t i = 0, n = liste_arr_d.size(); i < n;i++)
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
        }*/
        qDebug()<<"avt d size = "<<liste_avant_d.size();
        qDebug()<<"avt g size = "<<liste_avant_g.size();
        qDebug()<<"arr d size = "<<liste_arr_d.size();
        qDebug()<<"arr g size = "<<liste_arr_g.size();
        qDebug()<<"avt d enn size = "<<liste_avant_d_enn.size();
        qDebug()<<"avt g enn size = "<<liste_avant_g_enn.size();
        qDebug()<<"arr d enn size = "<<liste_arr_d_enn.size();
        qDebug()<<"arr g enn size = "<<liste_arr_g_enn.size();
}
