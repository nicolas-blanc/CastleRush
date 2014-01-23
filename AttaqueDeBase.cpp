#include "AttaqueDeBase.h"

AttaqueDeBase::AttaqueDeBase(int portee)
: Attaque(portee) {}

AttaqueDeBase::AttaqueDeBase(int portee, int deg)
: Attaque(portee,deg) {}

void AttaqueDeBase::lancerAttaque(Case* c) {
    //animationAttaque()
    c->transmettreAttaque(this->getDegat());
}
