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
#include <QMessageBox>

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
            parent()->afficheInfoUnite(getOccupant());
            parent()->setSelect(getOccupant());
            if (m_batiment) {
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
            parent()->getSelect()->setSelected(true);
            parent()->setFlag(attente);
            parent()->highlight(this);
            this->parent()->updatePopPt();
            this->parent()->setBoutons(unite, ((Unite*)parent()->getSelect())->getJoueur()->getNumero());
            this->parent()->afficheInfoUnite(this->getOccupant());
            parent()->CapturePossible(this);
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
            parent()->setBoutons(batChateau, ch->getJoueur()->getNumero());
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

void Case::transmettreAttaque(int nbPV, Entite*e) {
    if (m_occupant!=NULL) {
        if(e->Getnom() == "Chevalier"
           || e->Getnom() == "Archer"
           || e->Getnom() == "Pretre"
           || e->Getnom() == "Magicien"
           || e->Getnom() == "Voleur"
           || e->Getnom() == "Guerrier")
           m_occupant->modifierVie(nbPV + ((Unite*)e)->getBonusUnite()[1]);
        else
        {
           m_occupant->modifierVie(nbPV);
        }

        if (!contientBatiment()&&isOccupee() &&getOccupant()->getVie()==0){
            QPixmap *tombe;
            tombe=new QPixmap("images/Coffin.png");
            (getOccupant())->setPixmap(tombe->copy(0,96,32,32));

            getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
            setOccupant(NULL);
        }
        else if(isOccupee() && getOccupant()->Getnom()== "Chateau" && getOccupant()->getVie()==0)
        {
            QPixmap *tombe;
            tombe=new QPixmap("images/ChateauDetruit.png");
            (getOccupant())->setPixmap(tombe->copy(0,96,32,32));

            QMessageBox popup;
            popup.setText("Victoire " + this->getOccupant()->getJoueur()->getPseudo() + "!");
            popup.exec();

             this->getOccupant()->getPosition()[0]->parent()->finDuJeu();

        }
        else if(isOccupee() && getOccupant()->Getnom() == "Tour" && getOccupant()->getVie()==0)
        {
            QPixmap *tombe;
            tombe=new QPixmap("images/TourDetruite.png");
            (getOccupant())->setPixmap(tombe->copy(0,96,32,32));

            this->parent()->supprimerTour((Batiment*)this->getOccupant());
            getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
            setOccupant(NULL);
        }

    }
}

bool Case::isOccupee() {
    return (m_occupant != NULL);
}

void Case::declencherEffets(Joueur *joueur) {
    vector<Effet*>::iterator it = m_effets.begin();
    for(unsigned int i = 0; i < m_effets.size() ;i++) {
        if(m_effets[i]->getJoueur() == joueur)
        {
            if(m_effets[i]->decreaseTour())
            {
                parent()->highlight(this,-1,Qt::transparent,true);
                bool vrai = ((Unite*)this->getUnite())->enleverEffet(m_effets[i]);
                if(vrai)
                {
                    ((MalusMouvement*)m_effets[i])->enleverEffetUnite(this);
                }
                enleverEffet(it);
                vrai=false;
            }
        }
        it++;
    }
}
