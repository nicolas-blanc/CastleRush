#include "Archer.h"
Archer::Archer(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent, 5,2,1,5,0,c,j,"Archer")
{
    QPixmap* arch;
    if (j && j->getNumero()==0) {
        arch=new QPixmap("images/ArcherBleu.png");
    }
    else
        arch=new QPixmap("images/ArcherRouge.png");
    this->setPixmap(arch->copy(0,0,32,32));
    this->setOffset(offset().x()+3,offset().y()+3);
}
