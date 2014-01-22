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
    j->setUnite(this);
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
    Entite::modifierVie(vie);/*
    if (estMort())
        this->getJoueur()->deleteUnite(this);*/
}

bool Unite::attaquer(Case* c, Attaque* attaque) {
    bool attaquer;

    if(c->getOccupant()->getJoueur()!= ((Case*)parentItem())->parent()->getJoueurTour())
    {
                    if (getJoueur()->getPtAction()<attaque->getPtAction()) {
                        cout << "erreur PtAction" << flush;
                        attaquer = false;
                    }
                    else if ((abs(c->getX() - this->getPosition()[0]->getX()) + abs(c->getY() - this->getPosition()[0]->getY())) > attaque->getPortee()) {
                       cout << "erreur Portee," <<flush;
                       attaquer = false;
                    }
                    else
                    {
                    attaque->lancerAttaque(c);
                    if (((c->getOccupant())->getVie())==0){
                        QPixmap *tombe;
                        tombe=new QPixmap("images/Coffin.png");
                        (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));
                        sleep(1);

                        c->getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
                        c->setOccupant(NULL);
                    }
                    this->getJoueur()->modifPtAction(this->getCout());
                    attaquer = true;
                    }
    }
    else
    {
        cout << "erreur Attaque Perso" << flush;
        attaquer = false;
    }
    return attaquer;
}

bool Unite::attaquer(Case* c) {
    return attaquer(c,m_AttaqueParDefaut);
}

void Unite::attaquer(Entite* e) {
    int i =0;
    bool Attaquer = false;
    while(i<e->getPosition().size() && !Attaquer)
    {
       Attaquer = this->attaquer(e->getPosition()[i]);
       i++;
    }
}

void Unite::attaquer(Entite* e, Attaque* a) {
    int i =0;
    bool Attaquer = false;
    while(i<e->getPosition().size() && !Attaquer)
    {
    Attaquer = this->attaquer(e->getPosition()[i],a);
    i++;
    }
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
