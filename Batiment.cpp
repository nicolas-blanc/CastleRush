#include "Batiment.h"

Batiment::Batiment(QGraphicsItem * parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax)
: Entite(parent, ensCase, j, nom, vieMin, vieMax)
{
    if (getJoueur())
        m_Joueur->setBatiment(this);
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this,true);
}

