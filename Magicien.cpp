#include "Magicien.h"

Magicien::Magicien(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Magicien")
{
    QPixmap* mage;
    if (j && j->getNumero()==0) {
        mage=new QPixmap("images/MagicienneBleu.png");
    }
    else
        mage=new QPixmap("images/MagicienneRouge.png");
    setPixmap(mage->copy(0,0,32,32));
    setOffset(offset().x()+3,offset().y()+3);
}
