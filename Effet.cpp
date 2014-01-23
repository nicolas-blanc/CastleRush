#include "Effet.h"

Effet::Effet(int tour) {
    m_nbTour = tour;
}

bool Effet::decreaseTour() {
    m_nbTour--;
    if(m_nbTour == 0)
        return true;
    else
        return false;
}

void Effet::appliquerEffetCase(Case * c) {
    c->ajouterEffet(this);
}

DegenVie::DegenVie(int nbTour, int malus) : Effet(nbTour) { m_malus = malus; }

void DegenVie::appliquerEffetUnite(Case *c) {
    c->getUnite()->modifierVie(m_malus);
}

MalusMouvement::MalusMouvement(int nbTour, int malus) : Effet(nbTour) { m_malus = malus; }

void MalusMouvement::appliquerEffetUnite(Case *c) {
    ((Unite*) c->getUnite())->modifBonus(5,m_malus);
}

BonusDegat::BonusDegat(int nbTour, int bonus) : Effet(nbTour) { m_bonus = bonus; }

void BonusDegat::appliquerEffetUnite(Case *c) {
    ((Unite*) c->getUnite())->modifBonus(1,m_bonus);
}
