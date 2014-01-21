#include "Batiment.h"
#include "Plateau.h"

Batiment::Batiment(QGraphicsItem * parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax)
: Entite(parent, ensCase, j, nom, vieMin, vieMax)
{
    if (getJoueur())
        m_Joueur->setBatiment(this);
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this,true);
}

Batiment::Batiment(QGraphicsItem *parent, Case *c, Joueur *j, string nom, int vieMin, int vieMax)
: Entite(parent, *new vector<Case*>(1,c), j, nom, vieMin, vieMax)
{
    if (getJoueur())
        m_Joueur->setBatiment(this);
    c->setOccupant(this,true);
}

void Batiment::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Entite::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->cacheInfoUnite();
    ((Case*)parentItem())->parent()->afficheInfoUnite(this);
    ((Case*)parentItem())->parent()->eteindreButtons();

}
