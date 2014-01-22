#include "Batiment.h"
#include "Plateau.h"

Batiment::Batiment(QGraphicsItem * parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax)
: Entite(parent, ensCase, j, nom, vieMin, vieMax)
{
    if(nom == "Chateau")
    {
        j->setChateau(this);
    }
    else
    {
        j->setBatiment(this);
    }
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this,true);
}

Batiment::Batiment(QGraphicsItem * parent, vector<Case*>& ensCase, string nom, int vieMin, int vieMax)
: Entite(parent, ensCase, nom, vieMin, vieMax)
{
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this,true);
}

Batiment::Batiment(QGraphicsItem *parent, Case *c, Joueur *j, string nom, int vieMin, int vieMax)
: Entite(parent, *new vector<Case*>(1,c), j, nom, vieMin, vieMax)
{
    j->setBatiment(this);
    c->setOccupant(this,true);
}

Batiment::Batiment(QGraphicsItem *parent, Case *c, string nom, int vieMin, int vieMax)
: Entite(parent, *new vector<Case*>(1,c), nom, vieMin, vieMax)
{
    c->setOccupant(this,true);
}

void Batiment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Entite::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->setBoutons(batiment);
}
