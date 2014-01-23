#include "Tour.h"
#include "Case.h"
#include "Plateau.h"

#include <math.h>

Tour::Tour(QGraphicsItem* parent, Case* c, Joueur* j, string nom)
: Batiment(parent, c, j, nom, 0, 10)
{
    setPixmap(* new QPixmap("images/Tour1"));
    this->setAttaqueDeBase();
}

Tour::Tour(QGraphicsItem* parent, Case* c, string nom)
: Batiment(parent, c, nom, 0, 10)
{
    setPixmap(* new QPixmap("images/Tour1"));
    this->setAttaqueDeBase();
}

void Tour::setAttaqueDeBase() {
    m_attaque = new AttaqueDeBase(2,1,this);
}


void Tour::attaquer(Case* c) {
    getAttaque()->lancerAttaque(c);
}


void Tour::attaqueAuto() {
    Unite* u = ((Case*)parentItem())->parent()->getUniteAttaqueTour(this);
    if(u != NULL && u->getJoueur()->getNumero()!=this->getJoueur()->getNumero())
    {
        attaquer(u->getPosition()[0]);
    }
    else
        cout << "pas d'unite presente" << endl << flush;
}

void Tour::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Batiment::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->setBoutons(batTour);
}
