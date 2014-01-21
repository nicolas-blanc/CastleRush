#include "Chevalier.h"

Chevalier::Chevalier(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,1,2,1,5,0,c,j,"Chevalier")
{
    QPixmap* chev;
    if (j && j->getNumero()==0) {
        chev=new QPixmap("images/ChevalierBleu.png");
    }
    else
        chev=new QPixmap("images/ChevalierRouge.png");
    this->setPixmap(chev->copy(0,0,36,36));
}
