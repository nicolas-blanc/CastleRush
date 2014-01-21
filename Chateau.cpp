#include "Chateau.h"
#include "enumerations.h"
#include <math.h>
#include <QPixmap>
#include "Plateau.h"

Chateau::Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, Joueur* j, string nom) : Batiment(parent, EnsCase, j, nom, 0, 20) {
    if (j && j->getNumero()==0)
        this->setPixmap(* new QPixmap("images/ChateauBleu.png"));
    else
        this->setPixmap(* new QPixmap("images/ChateauRouge.png"));
}

void Chateau::Invoquer(int unite, Case * c)
{
    bool invoc_possible = adjacent(c);
    Unite* u;

    switch(unite) {
        case 1: {
            u = new Guerrier(this->parentItem(), c, this->getJoueur());
            break;}
        case 2: {
            u = new Archer(this->parentItem(), c, getJoueur());
            break; }
        case 3: {
            u = new Chevalier(this->parentItem(), c, getJoueur());
            break;}
        case 4:{
            u = new Magicien(this->parentItem(), c, getJoueur());
            break;}
        case 5:{
            u = new Pretre(this->parentItem(), c, getJoueur());
            break;}
        default:{
            u = new Voleur(this->parentItem(), c, getJoueur());
            break;}
    }

    if(this->getJoueur()->getPopulation()+u->getPopulation() <= getJoueur()->getPopulationMax()
            && this->getJoueur()->getPtAction()-u->getCout()>=0
            && invoc_possible)
    {
        getJoueur()->setUnite(u);
        this->getJoueur()->modifPopulation(u->getPopulation());
        this->getJoueur()->modifPtAction(u->getCout());
    }
    else
    {
        delete(u);
        if(this->getJoueur()->getPopulation()+u->getPopulation() >= getJoueur()->getPopulationMax())
        {
            cout << "erreur pop"<<flush;
            //throw ManquePopulation();
        }
        else if (this->getJoueur()->getPtAction()-u->getCout()<0)
        {
            cout << "erreur Pt"<<flush;
            //throw ManquePtAction();
        }
        else if(!adjacent(c))
        {
            cout << "erreur portee"<<flush;
            //throw ManquePortee();
        }
        else
            cout << "et merde !"<<flush;
    }
}


void Chateau::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Batiment::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->uniteInvocable();
}
