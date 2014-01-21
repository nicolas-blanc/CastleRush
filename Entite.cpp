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

Entite::~Entite()
{
    //dtor
}

bool Entite::adjacent(Case* c) {
    bool adj=false;
    unsigned int i=0;
    while(i<getPosition().size() && !adj) {
        adj=(((c->getX()+getPosition()[i]->getX())==0||(c->getX()-getPosition()[i]->getX())==0||(c->getX()-getPosition()[i]->getX())==1||(c->getX()+getPosition()[i]->getX())==1)
             &&((c->getY()-getPosition()[i]->getY())==0||(c->getY()-getPosition()[i]->getY())==0||(c->getY()-getPosition()[i]->getY())==1||(c->getY()+getPosition()[i]->getY())==1)
                && !c->isOccupee());
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
    this->setOffset(OFFSET+(m_position[0]->getX()*SIZE),OFFSET+(m_position[0]->getY()*SIZE));
    setSelected(true);
}

void Entite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsPixmapItem::mouseReleaseEvent(event);
    if (((Case*)parentItem())->parent()->getFlag()==deplacement) {
        ((Case*)parentItem())->parent()->setFlag(attente);
        ((Case*)parentItem())->parent()->highlight(((Case*)parentItem()));
    }

    ((Case*)parentItem())->parent()->setSelect(this);
}
