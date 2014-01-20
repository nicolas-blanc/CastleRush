#include "Guerrier.h"

Guerrier::Guerrier(QGraphicsItem * parent, vector<Case*> ensCase, Joueur* j)
:Unite(parent,5,2,3,7,0,ensCase,j,"Guerrier")
{
}

Guerrier::~Guerrier() {
}

