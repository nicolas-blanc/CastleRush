#include "Chateau.h"
#include "enumerations.h"
#include <math.h>
#include <QPixmap>

Chateau::Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, Joueur* j, string nom) : Batiment(parent, EnsCase, j, nom, 0, 20) {
    this->setPixmap(* new QPixmap("ChateauCentral.png"));
}

void Chateau::Invoquer(int unite, Case * c)
{
    bool invoc_possible = adjacent(c);

    vector<Case *> ensCase;
    ensCase.push_back(c);
    Unite* u;

    switch(unite) {
        case guerrier: {
            u = new Guerrier(this->parentItem(), ensCase, this->getJoueur());
            break;}
        case archer: {
            u = new Archer(this->parentItem(), ensCase, getJoueur());
            break; }
        case chevalier: {
            u = new Chevalier(this->parentItem(), ensCase, getJoueur());
            break;}
        case magicien:{
            u = new Magicien(this->parentItem(), ensCase, getJoueur());
            break;}
        case pretre:{
            u = new Pretre(this->parentItem(), ensCase, getJoueur());
            break;}
        default:{
            u = new Voleur(this->parentItem(), ensCase, getJoueur());
            break;}
    }

    if(this->getJoueur()->getPopulation()+u->getPopulation() <= getJoueur()->getPopulationMax() && this->getJoueur()->getPtAction() >= u->getCout() && invoc_possible)
    {
        getJoueur()->setUnite(u);
        this->getJoueur()->modifPopulation(u->getPopulation());
        this->getJoueur()->modifPtAction(u->getCout());
    }
    else
    {
        delete(u);
        if(this->getJoueur()->getPopulation()+u->getPopulation() >= getJoueur()->getPopulationMax())
            throw ManquePopulation();
        else if (this->getJoueur()->getPtAction() <= u->getCout())
            throw ManquePtAction();
        else
            throw ManquePortee();
    }
}
