#include "Voleur.h"

Voleur::Voleur(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Voleur")
{
    QPixmap* vol;
    if (j && j->getNumero()==0) {
        vol=new QPixmap("images/VoleurBleu.png");
    }
    else
        vol=new QPixmap("images/VoleurRouge.png");
    this->setPixmap(vol->copy(0,0,32,32));
    this->setOffset(offset().x()+3,offset().y()+3);
}
