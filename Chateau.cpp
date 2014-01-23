#include "Chateau.h"
#include <math.h>
#include <QPixmap>
#include "Plateau.h"
#include "QMessageBox"

Chateau::Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, Joueur* j, string nom) : Batiment(parent, EnsCase, j, nom, 0, 20) {
    if (j && j->getNumero()==0)
        this->setPixmap(* new QPixmap("images/ChateauBleu.png"));
    else
        this->setPixmap(* new QPixmap("images/ChateauRouge.png"));

}

Chateau::Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, string nom) : Batiment(parent, EnsCase, nom, 0, 20) {
        this->setPixmap(* new QPixmap("images/ChateauCentrale.png"));
}

bool Chateau::Invoquer(catUnite unite, Case * c){
    bool invoc_possible = adjacent(c);
    Unite* u;

    switch(unite) {
        case guerrier: {
            u = new Guerrier(c, c, this->getJoueur());
            break;}
        case archer: {
            u = new Archer(c, c, getJoueur());
            break; }
        case chevalier: {
            u = new Chevalier(c, c, getJoueur());
            break;}
        case magicien:{
            u = new Magicien(c, c, getJoueur());
            break;}
        case pretre:{
            u = new Pretre(c, c, getJoueur());
            break;}
        default:{
            u = new Voleur(c, c, getJoueur());
            break;}
    }

    if(this->getJoueur()->getPopulation()+u->getPopulation() <= getJoueur()->getPopulationMax()
            && this->getJoueur()->getPtAction()-u->getCout()>=0
            && invoc_possible)
    {
        this->getJoueur()->modifPopulation(u->getPopulation());
        this->getJoueur()->modifPtAction(u->getCout());
        return true;
    }
    else
    {
        c->setOccupant(NULL);
        delete u;
        if(this->getJoueur()->getPopulation()+u->getPopulation() >= getJoueur()->getPopulationMax())
        {
            QMessageBox popup;
            popup.setText("Vous n'avez pas assez de point de population!");
            popup.exec();
        }
        else if (this->getJoueur()->getPtAction()-u->getCout()<0)
        {
            QMessageBox popup;
            popup.setText("Vous n'avez pas assez de point d'action!");
            popup.exec();
        }
        else
        {
            cout << "erreur portee"<<flush;
        }
        return false;
    }
}

void Chateau::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Batiment::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->setBoutons(batChateau,this->getJoueur()->getNumero());
}
