#include "Chateau.h"
#include "enumerations.h"
#include <math.h>
#include <QPixmap>

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
        case guerrier: {
            u = new Guerrier(this->parentItem(), c, this->getJoueur());
            break;}
        case archer: {
            u = new Archer(this->parentItem(), c, getJoueur());
            break; }
        case chevalier: {
            u = new Chevalier(this->parentItem(), c, getJoueur());
            break;}
        case magicien:{
            u = new Magicien(this->parentItem(), c, getJoueur());
            break;}
        case pretre:{
            u = new Pretre(this->parentItem(), c, getJoueur());
            break;}
        default:{
            u = new Voleur(this->parentItem(), c, getJoueur());
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
