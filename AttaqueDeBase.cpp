#include "AttaqueDeBase.h"

AttaqueDeBase::AttaqueDeBase(Entite *entite,int portee, int deg)
: Attaque(entite,portee,deg) {}

void AttaqueDeBase::lancerAttaque(Case* c) {
    //animationAttaque()
    c->transmettreAttaque(this->getDegat());
}
