#include "Archer.h"
Archer::Archer(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent, 5,2,1,5,0,c,j,"Archer")
{
    setAttaqueDeBase(5);
    this->initSort();
    QPixmap* arch;
    if (j && j->getNumero()==0) {
        arch=new QPixmap("images/ArcherBleu.png");
    }
    else
        arch=new QPixmap("images/ArcherRouge.png");

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(arch->copy(i*32,0,32,32)));
        this->setImageGauche(new QPixmap(arch->copy(i*32,32,32,32)));
        this->setImageDroite(new QPixmap(arch->copy(i*32,64,32,32)));
        this->setImageDos(new QPixmap(arch->copy(i*32,96,32,32)));
    }
    this->setImageFace(new QPixmap(arch->copy(32,0,32,32)));
    this->setImageGauche(new QPixmap(arch->copy(32,32,32,32)));
    this->setImageDroite(new QPixmap(arch->copy(32,64,32,32)));
    this->setImageDos(new QPixmap(arch->copy(32,96,32,32)));

    this->setPixmap(*(getImageFace()[1]));
}

void Archer::initSort() {
    v_sort["Concentration"] = new Concentration("Concentration",1,0,2,this);
}
