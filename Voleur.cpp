#include "Voleur.h"

Voleur::Voleur(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Voleur")
{
    Unite::setAttaqueDeBase(this);
    this->initSort();
    QPixmap* vol;
    if (j && j->getNumero()==0) {
        vol=new QPixmap("images/VoleurBleu.png");
    }
    else
        vol=new QPixmap("images/VoleurRouge.png");

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(vol->copy(i*32,0,32,32)));
        this->setImageGauche(new QPixmap(vol->copy(i*32,32,32,32)));
        this->setImageDroite(new QPixmap(vol->copy(i*32,64,32,32)));
        this->setImageDos(new QPixmap(vol->copy(i*32,96,32,32)));
    }
    this->setImageFace(new QPixmap(vol->copy(32,0,32,32)));
    this->setImageGauche(new QPixmap(vol->copy(32,32,32,32)));
    this->setImageDroite(new QPixmap(vol->copy(32,64,32,32)));
    this->setImageDos(new QPixmap(vol->copy(32,96,32,32)));

    this->setPixmap(*(getImageFace()[1]));
}

void Voleur::initSort() {
    v_sort["Coup Empoisonné"] = new AttaqueEmpoisonnee(this,"Coup Empoisonné",1,1,3);
}
