#include "Guerrier.h"

Guerrier::Guerrier(QGraphicsItem * parent, Case* c, Joueur* j)
:Unite(parent,5,2,3,7,0,c,j,"Guerrier")
{
    this->setAttaqueDeBase();
    this->initSort();
    QPixmap* gue;
    if (j && j->getNumero()==0) {
        gue=new QPixmap("images/GuerrierBleu.png");
    }
    else
        gue=new QPixmap("images/GuerrierRouge.png");
    this->setPixmap(gue->copy(0,0,32,32));
    this->setOffset(offset().x()+3,offset().y()+3);
}

Guerrier::~Guerrier() {
}

void Guerrier::initSort() {
    v_sort["Attaque Puissante"] = new AttaquePuissante("Attaque Puissante",2,1,3);
}
