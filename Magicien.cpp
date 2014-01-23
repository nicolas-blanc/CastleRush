#include "Magicien.h"

Magicien::Magicien(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Magicien")
{
    Unite::setAttaqueDeBase(this,2);
    this->initSort();
    QPixmap* mage;
    if (j && j->getNumero()==0) {
        mage=new QPixmap("images/MagicienneBleu.png");
    }
    else
        mage=new QPixmap("images/MagicienneRouge.png");

    for (int i=0;i<3;i++){
        this->setImageFace(new QPixmap(mage->copy(i*32,0,32,32)));
        this->setImageGauche(new QPixmap(mage->copy(i*32,32,32,32)));
        this->setImageDroite(new QPixmap(mage->copy(i*32,64,32,32)));
        this->setImageDos(new QPixmap(mage->copy(i*32,96,32,32)));
    }
    this->setImageFace(new QPixmap(mage->copy(32,0,32,32)));
    this->setImageGauche(new QPixmap(mage->copy(32,32,32,32)));
    this->setImageDroite(new QPixmap(mage->copy(32,64,32,32)));
    this->setImageDos(new QPixmap(mage->copy(32,96,32,32)));

    this->setPixmap(*(getImageFace()[1]));
}

void Magicien::initSort() {
    v_sort["Glyphe de Gel"] = new GlypheGel(this,"Glyphe de Gel",3,4);
}
