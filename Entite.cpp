#include "Entite.h"
#include "Plateau.h"

#define SIZE 36
#define OFFSET 0

Entite::Entite(QGraphicsItem * parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax)
: QGraphicsPixmapItem(parent), m_vie(vieMax,vieMin), m_position(ensCase) {
    setJoueur(j);
    Setnom(nom);
    this->setOffset(OFFSET+(ensCase[0]->getX()*SIZE),OFFSET+(ensCase[0]->getY()*SIZE));
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

Entite::Entite(QGraphicsItem * parent, vector<Case*>& ensCase, string nom, int vieMin, int vieMax)
: QGraphicsPixmapItem(parent), m_vie(vieMax,vieMin), m_position(ensCase) {
    setJoueur(NULL);
    Setnom(nom);
     this->setOffset(OFFSET+(ensCase[0]->getX()*SIZE),OFFSET+(ensCase[0]->getY()*SIZE));
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

Entite::~Entite()
{
    //dtor
}

bool Entite::adjacent(Case* c) {
    bool adj=false;
    unsigned int i=0;
    while(i<getPosition().size() && !adj) {
        adj=(  ((getPosition()[i]->getX()-c->getX()==0)&&(getPosition()[i]->getY()-c->getY()==0))
             ||((abs(getPosition()[i]->getX()-c->getX()))==1&&(getPosition()[i]->getY()-c->getY()==0))
             ||((getPosition()[i]->getX()-c->getX()==0)&&(abs(getPosition()[i]->getY()-c->getY())==1)));
        adj = adj&&!c->isOccupee();
        i++;
    }
    return adj;
}

void Entite::modifierVie(int vie) {
    m_vie.modifVie(vie);
}

void Entite::setPosition(vector<Case *> position) {
    for (unsigned int i=0; i<m_position.size(); i++)
        m_position[i]->setOccupant(NULL);
    m_position = position;
    for (unsigned int i=0; i<m_position.size(); i++)
        m_position[i]->setOccupant(this);
    setParentItem(m_position[0]);
    //this->setOffset(OFFSET+(m_position[0]->getX()*SIZE),OFFSET+(m_position[0]->getY()*SIZE));
    setSelected(true);
}

void Entite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    if (((Case*)parentItem())->parent()->getFlag()==deplacement) {
        ((Case*)parentItem())->parent()->highlight(((Case*)parentItem()));
        ((Case*)parentItem())->parent()->setSelect(this);
        ((Case*)parentItem())->parent()->setBoutons(unite, getJoueur()->getNumero());
        ((Case*)parentItem())->parent()->afficheInfoUnite(this);
    }
    else if (((Case*)parentItem())->parent()->getFlag()==attente) {
        ((Case*)parentItem())->parent()->afficheInfoUnite(this);
        ((Case*)parentItem())->parent()->setSelect(this);
    }
    else if (((Case*)parentItem())->parent()->getFlag()==attaque) {
        this->setSelected(false);
        ((Unite*)(((Case*)parentItem())->parent()->getSelect()))->setSelected(true);
        ((Unite*)(((Case*)parentItem())->parent()->getSelect()))->attaquer(this);
        Case* c = (Case*)parentItem();
        ((Case*)parentItem())->parent()->highlight(c);
        ((Case*)parentItem())->parent()->updatePopPt();
    } else if (((Case*)parentItem())->parent()->getFlag()==attaqueSort) {
        ((Unite*)(((Case*)parentItem())->parent()->getSelect()))->attaquer(this,((Case*)parentItem())->parent()->getChoixSort());
        ((Case*)parentItem())->parent()->setFlag(attente);
        ((Case*)parentItem())->parent()->highlight((Case*)parentItem());
        ((Case*)parentItem())->parent()->updatePopPt();
    }
}


