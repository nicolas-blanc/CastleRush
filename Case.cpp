#include "Case.h"
#include "Effet.h"
#include "Plateau.h"
#include <QtGui>
#include <QBrush>
#include <math.h>
#include "Chateau.h"
#include "enumerations.h"

#define SIZE 36


Case::Case(int x, int y, QObject* parent) : QGraphicsRectItem(x*SIZE,y*SIZE,SIZE,SIZE), QObject(parent){
    m_x=x;
    m_y=y;
    m_occupant=NULL;
    m_batiment = false;
    isSelected = false;
    setFlags(QGraphicsItem::ItemIsSelectable);
}

void Case::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseReleaseEvent(event);
    if (parent()->getFlag()==attente) {
        this->setSelected(true);
        this->parent()->setSelect(this);
        parent()->setBoutons(carre);
    }
    else if (parent()->getFlag()==deplacement) {
        ((Unite*)(parent()->getSelect()))->deplacer(this);
        parent()->setFlag(attente);
        parent()->highlight(this);
        this->parent()->updatePopPt();
    }
    else if (parent()->getFlag()==attaque) {
        ((Unite*)(parent()->getSelect()))->attaquer(this);
        parent()->setFlag(attente);
        parent()->highlightAttaque(this);
        this->parent()->updatePopPt();
    }
    else if (parent()->getFlag()==invoquer){
        Chateau* ch=((Chateau*)(parent()->getSelect()));
        ch->Invoquer(parent()->getUnitInvoc(), this);
        parent()->updatePopPt();
        parent()->setFlag(attente);
    }
}

Plateau* Case::parent()  {
    return (Plateau*)QObject::parent();
}

void Case::setOccupant(Entite* occ, bool bat) {
    m_occupant = occ;
    m_batiment = bat;
}

void Case::transmettreAttaque(int nbPV) {
    if (m_occupant!=NULL) {
            m_occupant->modifierVie(nbPV);
    }
}

bool Case::isOccupee() {
    return (m_occupant != NULL);
}

void Case::declencherEffets() {
    int vectSize = m_effets.size();
    for (int i=0; i<vectSize; i++) {
        m_effets[i]->getSort()->lancerAttaque(this);
        m_effets[i]->decreaseTour();
    }
}
