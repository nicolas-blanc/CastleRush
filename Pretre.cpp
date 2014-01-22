#include "Pretre.h"

Pretre::Pretre(QGraphicsItem * parent, Case* c, Joueur* j) : Unite(parent,5,2,1,5,0,c,j,"Pretre")
{
    this->setAttaqueDeBase();
    this->initSort();
    QPixmap* pret;
    if (j && j->getNumero()==0) {
        pret=new QPixmap("images/PretresseBleu.png");
    }
    else
        pret=new QPixmap("images/PretresseRouge.png");
    this->setPixmap(pret->copy(0,0,32,32));
    this->setOffset(offset().x()+3,offset().y()+3);
}

void Pretre::initSort() {
    v_sort["Soin"] = new Soin("Soin",-2,3,3);
}
