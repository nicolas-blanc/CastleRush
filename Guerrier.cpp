#include "Guerrier.h"

Guerrier::Guerrier(QGraphicsItem * parent, Case* c, Joueur* j)
:Unite(parent,5,2,3,7,0,c,j,"Guerrier")
{
    QPixmap* chev;
    if (j && j->getNumero()==0) {
        chev=new QPixmap("images/GuerrierBleu.png");
    }
    else
        chev=new QPixmap("images/GuerrierRouge.png");
    this->setPixmap(chev->copy(0,0,32,32));
    this->setOffset(offset().x()+3,offset().y()+3);
}

Guerrier::~Guerrier() {
}
