#include "Unite.h"
#include "ListeException.h"
#include "Plateau.h"
#include <exception>
#include <QMessageBox>
#include <math.h>

Unite::Unite(QGraphicsItem * parent, unsigned int mvt, unsigned int ct, unsigned int pop, int vieMax, int vieMin, Case* c, Joueur* j, string nom)
: Entite(parent, *new vector<Case*>(1,c),j,nom,vieMin,vieMax), v_dep_face(), v_dep_gauche(), v_dep_droite(), v_dep_dos() {
    this->setMouvement(mvt);
    this->setCout(ct);
    this->setPopulation(pop);
    this->setAttaqueDeBase();

}

void Unite::setAttaqueDeBase() {
    m_AttaqueParDefaut = new AttaqueDeBase();
    m_AttaqueParDefaut->lierEntite(this);
}

void Unite::deplacer(Case* c) {
    int mvt = this->mouvementDemande(c);
    if(deplacementPossible(c))
    {
        if(this->getJoueur()->getPtAction()-mvt >=0)
        {
            vector<Case*> position;
            position.push_back(c);
            this->setPosition(position);
            this->getJoueur()->modifPtAction(mvt);
            ((Plateau*)((Case*)this->parentItem())->parent())->setFlag(attente);
        }
        else
        {
            QMessageBox popup;
            popup.setText("Vous n'avez pas assez de point d'action !");
            popup.exec();
        }
    }
    else
    {
        QMessageBox popup;
        popup.setText("Cette unité ne peut se déplacer autant !");
        popup.exec();
    }
}

int Unite::mouvementDemande(Case* c)
{
    return abs(c->getX()-this->getPosition()[0]->getX())+abs(c->getY()-this->getPosition()[0]->getY());
}

bool Unite::deplacementPossible(Case* c) {
    return ((getMouvement()+getJoueur()->getListeBonusJoueur()[5]>=
            abs(c->getX()-this->getPosition()[0]->getX())+abs(c->getY()-this->getPosition()[0]->getY()))
            && !c->isOccupee());
}

void Unite::modifierVie(int vie) {
    Entite::modifierVie(vie);
    if (estMort())
        this->getJoueur()->deleteUnite(this);
}

void Unite::attaquer(Case* c, Attaque* attaque) {
    if (getJoueur()->getPtAction()<attaque->getPtAction()) {
        ManquePtAction ex;
        throw ex;
    }
    Case* cE = getPosition()[0];
    if ((abs(c->getX() - cE->getX()) + abs(c->getY() - cE->getY())) <= attaque->getPortee()) {
        ManquePortee ex;
        throw ex;
    }
    attaque->lancerAttaque(c);
}

void Unite::attaquer(Case* c) {
    attaquer(c,m_AttaqueParDefaut);
}

int Unite::getMouvement() {
    return m_mouvement;
}

Unite::~Unite() {

}

void Unite::initSort() {

}

void Unite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Entite::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->setBoutons(unite, getJoueur()->getNumero());

}

//Penser � supprimer l'effet quand il arrive � 0 tours
