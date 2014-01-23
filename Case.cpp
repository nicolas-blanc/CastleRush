#include "Case.h"
#include "Entite.h"
#include "Unite.h"
#include "Effet.h"
#include "Plateau.h"
#include "Chateau.h"
#include "enumerations.h"
#include "Joueur.h"
#include <QtGui>
#include <QBrush>
#include <math.h>

#define SIZE 36


Case::Case(int x, int y, QObject* parent) : QGraphicsRectItem(x*SIZE,y*SIZE,SIZE,SIZE), QObject(parent){
    m_x=x;
    m_y=y;
    m_occupant=NULL;
    m_batiment = false;
    isSelected = false;
    glyphe = false;
    setFlags(QGraphicsItem::ItemIsSelectable);
}

void Case::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    QGraphicsRectItem::mouseReleaseEvent(event);
    if (parent()->getFlag()==attente) {
        parent()->highlight(this);
        if (isOccupee()) {
            cout<<"test"<<flush;
            parent()->afficheInfoUnite(getOccupant());
            parent()->setSelect(getOccupant());
            if (m_batiment) {
                cout<<"test2"<<flush;
                if (getOccupant()->Getnom()=="Chateau")
                    parent()->setBoutons(batChateau, getOccupant()->getJoueur()->getNumero());
                else {
                    if (getOccupant()->getJoueur())
                        parent()->setBoutons(batiment, getOccupant()->getJoueur()->getNumero());
                    else
                        parent()->setBoutons(batiment);
                }
            }
            else
                parent()->setBoutons(unite, getOccupant()->getJoueur()->getNumero());

        }
        else {
            this->setSelected(true);
            this->parent()->setSelect(this);
            parent()->setBoutons(carre);
        }
    }
    else if (parent()->getFlag()==deplacement) {
        this->setSelected(false);
        if (!((Unite*)parent()->getSelect())->deplacer(this)) {
            parent()->setFlag(attente);
            this->mouseReleaseEvent(event);
        }
        else {
            parent()->CapturePossible(this);
            parent()->getSelect()->setSelected(true);
            parent()->setFlag(attente);
            parent()->highlight(this);
            this->parent()->updatePopPt();
        }
    }
    else if (parent()->getFlag()==attaque) {
        if (!isOccupee()) {
            parent()->setFlag(attente);
            this->mouseReleaseEvent(event);
        }
        else {
            this->setSelected(false);
            parent()->getSelect()->setSelected(true);
            ((Unite*)(parent()->getSelect()))->attaquer(this);
            parent()->setFlag(attente);
            parent()->highlight(this);
            this->parent()->updatePopPt();
        }
    }
    else if (parent()->getFlag()==attaqueSort) {
        ((Unite*)(parent()->getSelect()))->attaquer(this,parent()->getChoixSort());
        parent()->setFlag(attente);
        parent()->highlight(this);
    }
    else if (parent()->getFlag()==invoquer){
        this->setSelected(false);
        Chateau* ch=((Chateau*)(parent()->getSelect()));
        if (!ch->Invoquer(parent()->getUnitInvoc(), this)) {
            parent()->setFlag(attente);
            this->mouseReleaseEvent(event);
        }
        else {
            parent()->getSelect()->setSelected(true);
            parent()->highlight(this);
            parent()->updatePopPt();
            parent()->setFlag(attente);
        }
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

void Case::declencherEffets(Joueur *joueur) {
    vector<Effet*>::iterator it = m_effets.begin();
    for(unsigned int i = 0; i < m_effets.size() ;i++) {
        if(isOccupee() && !(m_batiment)) {
            m_effets[i]->appliquerEffetUnite(this);
        }
        if(m_effets[i]->getJoueur() == joueur)
            if(m_effets[i]->decreaseTour())
                enleverEffet(it);
        it++;
    }
}
