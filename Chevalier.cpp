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
        this->setImageFace(chev->copy(i*36,0,36,36));
    }
    this->setPixmap(this->getImageFace(1));
}

void Chevalier::initSort() {
    v_sort["Charge"] = new Charge("Charge",2,1,3);
}
