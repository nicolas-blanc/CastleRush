#include "AttaqueDeBase.h"

AttaqueDeBase::AttaqueDeBase(int portee)
: Attaque(portee) {}

void AttaqueDeBase::lancerAttaque(Case* c) {
    c->transmettreAttaque(this->getDegat());
}