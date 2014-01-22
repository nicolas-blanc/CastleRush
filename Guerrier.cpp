#include "Guerrier.h"

Guerrier::Guerrier(QGraphicsItem * parent, Case* c, Joueur* j)
:Unite(parent,5,2,3,7,0,c,j,"Guerrier")
{
    QPixmap* guer;
    if (j && j->getNumero()==0) {
        guer=new QPixmap("images/GuerrierBleu.png");
    }
    else
        guer=new QPixmap("images/GuerrierRouge.png");

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(guer->copy(i*32,0,32,32)));
        this->setImageGauche(new QPixmap(guer->copy(i*32,32,32,32)));
        this->setImageDroite(new QPixmap(guer->copy(i*32,64,32,32)));
        this->setImageDos(new QPixmap(guer->copy(i*32,96,32,32)));
    }
    this->setImageFace(new QPixmap(guer->copy(32,0,32,32)));
    this->setImageGauche(new QPixmap(guer->copy(32,32,32,32)));
    this->setImageDroite(new QPixmap(guer->copy(32,64,32,32)));
    this->setImageDos(new QPixmap(guer->copy(32,96,32,32)));

    this->setPixmap(*(getImageFace()[1]));
}

Guerrier::~Guerrier() {
}
