#include "Pretre.h"

Pretre::Pretre(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Pretre")
{
    Unite::setAttaqueDeBase(this);
    this->initSort();
    QPixmap* pret;
    if (j && j->getNumero()==0) {
        pret=new QPixmap("images/PretresseBleu.png");
    }
    else
        pret=new QPixmap("images/PretresseRouge.png");

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(pret->copy(i*32,0,32,32)));
        this->setImageGauche(new QPixmap(pret->copy(i*32,32,32,32)));
        this->setImageDroite(new QPixmap(pret->copy(i*32,64,32,32)));
        this->setImageDos(new QPixmap(pret->copy(i*32,96,32,32)));
    }
    this->setImageFace(new QPixmap(pret->copy(32,0,32,32)));
    this->setImageGauche(new QPixmap(pret->copy(32,32,32,32)));
    this->setImageDroite(new QPixmap(pret->copy(32,64,32,32)));
    this->setImageDos(new QPixmap(pret->copy(32,96,32,32)));

    this->setPixmap(*(getImageFace()[1]));
}

void Pretre::initSort() {
    v_sort["Soin"] = new Soin(this,"Soin",-2,3,3);
}
