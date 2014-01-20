#include "BatimentBonusStat.h"

BatimentBonusStat::BatimentBonusStat(QGraphicsItem* parent, vector<Case*>& ensCase, Joueur* j, string nom, int stat) : Batiment(parent, ensCase, j, nom, -1, -1) {
    setStat(stat);
    setBonus(0);
    setNbTours(0);
}

void BatimentBonusStat::modifBonus() {
// Modifie le bonus dans le vector de joueur, en fonction du bonus et du nombre de tours
    m_NbTours++;

    switch(getStat()) {
        case 0:
            setBonus(getBonus() + getNbTours()/2);
            break;
        case 1:
            setBonus(getBonus() + getNbTours()/2);
            break;
        case 2:
            setBonus(getBonus() + getNbTours()/4);
            break;
        case 3:
            setBonus(getBonus() + getNbTours()/6);
            break;
        case 4:
            setBonus(getBonus() + getNbTours()/4);
            break;
        case 5:
            setBonus(getBonus() + getNbTours()/3);
            break;
        default:
            // appel d'exception
            break;
        }
    miseAJourBonus();
}

void BatimentBonusStat::Bonus() {
    switch(getStat()) {
        case 0:
            setBonus(5);
            break;
        case 1:
            setBonus(1/*nbToursTotal/2*/);//nbToursTotal variable global
            break;
        case 2:
            setBonus(1);
            break;
        case 3:
            setBonus(1);
            break;
        case 4:
            setBonus(1);
            break;
        case 5:
            setBonus(2);
            break;
        default:
            // appel exception
            break;
    }
    miseAJourBonus();
}

void BatimentBonusStat::randomStat() {
    setStat(rand_a_b(0, 7));
}

void BatimentBonusStat::changementProprio(Joueur j) {
    Entite::setJoueur(&j);
    getJoueur()->setBatiment(this);
    if(getStat()>1)
        randomStat();

    Bonus();
    setNbTours(0);
}

