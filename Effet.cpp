#include "Effet.h"
#include "Case.h"
#include "Joueur.h"

Effet::Effet(Joueur *joueur, int tour) {
    m_nbTour = tour;
    m_joueur = joueur;
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

DegenVie::DegenVie(Joueur * joueur, int nbTour, int malus) : Effet(joueur,nbTour) { m_malus = malus; }

void DegenVie::appliquerEffetUnite(Case *c) {
    c->getUnite()->modifierVie(m_malus);
}

MalusMouvement::MalusMouvement(Joueur *joueur, int nbTour, int malus) : Effet(joueur,nbTour) { m_malus = malus; }

void MalusMouvement::appliquerEffetUnite(Case *c) {
    ((Unite*) c->getUnite())->modifBonus(3,-m_malus);
}

BonusDegat::BonusDegat(Joueur * joueur,int nbTour, int bonus) : Effet(joueur,nbTour) { m_bonus = bonus; }

void BonusDegat::appliquerEffetUnite(Case *c) {
    ((Unite*) c->getUnite())->modifBonus(1,m_bonus);
}
