#include "Chevalier.h"

Chevalier::Chevalier(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,1,2,1,5,0,c,j,"Chevalier")
{
    this->setAttaqueDeBase();
    this->initSort();

    QPixmap* chev;

    if (j && j->getNumero()==0) {
        chev=new QPixmap("images/ChevalierBleu.png");
    }
    else {
        chev=new QPixmap("images/ChevalierRouge.png");
    }

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(chev->copy(i*36,0,36,36)));
        this->setImageGauche(new QPixmap(chev->copy(i*36,36,36,36)));
        this->setImageDroite(new QPixmap(chev->copy(i*36,64,36,36)));
        this->setImageDos(new QPixmap(chev->copy(i*36,96,36,36)));
    }
    this->setImageFace(new QPixmap(chev->copy(36,0,36,36)));
    this->setImageGauche(new QPixmap(chev->copy(36,36,36,36)));
    this->setImageDroite(new QPixmap(chev->copy(36,72,36,36)));
    this->setImageDos(new QPixmap(chev->copy(36,108,36,36)));

    this->setPixmap(*(getImageFace()[1]));
}

void Chevalier::initSort() {
    v_sort["Charge"] = new Charge("Charge",3,1,3,this);
}
