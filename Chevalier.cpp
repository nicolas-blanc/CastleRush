#include "Chevalier.h"

Chevalier::Chevalier(QGraphicsItem * parent, vector<Case*> ensCase, Joueur* j) : Unite(parent,1,2,1,5,0,ensCase,j,"Chevalier")
{
    QPixmap* chevBleu=new QPixmap("ChevalierBleu.png");
    this->setPixmap(chevBleu->copy(0,0,36,36));
}
