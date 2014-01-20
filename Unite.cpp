#include "Unite.h"
#include "ListeException.h"
#include "Plateau.h"
#include <exception>
#include <QMessageBox>
#include <math.h>

Unite::Unite(QGraphicsItem * parent, unsigned int mvt, unsigned int ct, unsigned int pop, int vieMax, int vieMin, vector<Case*>& ensCase, Joueur* j, string nom)
: Entite(parent, ensCase,j,nom,vieMin,vieMax) {
    this->setMouvement(mvt);
    this->setCout(ct);
    this->setPopulation(pop);
    this->setAttaqueDeBase();
    for (unsigned int i=0; i<ensCase.size(); i++)
        ensCase[i]->setOccupant(this);
    setFlags(QGraphicsItem::ItemIsSelectable);
}

void Unite::setAttaqueDeBase() {
    m_AttaqueParDefaut = new AttaqueDeBase();
    m_AttaqueParDefaut->lierEntite(this);
}

void Unite::deplacer(Case* c) {
    if(deplacement(c))
    {
    vector<Case*> position;
    position.push_back(c);
    this->setPosition(position);
    this->getJoueur()->setPtAction(this->getMouvement());
    ((Plateau*)((Case*)this->parentItem())->parent())->setFlag(attente);
    }
    else
    {
        cout << "erreur" << endl;
    }
}

bool Unite::deplacement(Case* c) {
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

//Penser � supprimer l'effet quand il arrive � 0 tours
