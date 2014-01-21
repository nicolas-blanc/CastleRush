#include "Joueur.h"

Joueur::Joueur(int couleur, int numero) : m_listeBonusJoueur() {
    m_couleur = couleur;
    m_numero = numero;

    for (unsigned int i=0; i<6; i++)
        m_listeBonusJoueur.push_back(0);
    setPtActionMax(20);
    setPtAction(20);
    setPopulationMax(100);
    setPopulation(0);

}

Joueur::~Joueur() {
}

void Joueur::setBatiment(Batiment * batiment) { 
    v_Batiment[batiment->Getnom()] = batiment; 
}

void Joueur::setUnite(Unite * unite) {
    v_Unite[unite->Getnom()] = unite; 
}

void Joueur::deleteBatiment(Batiment* bat) { 
    v_Batiment.erase(bat->Getnom()); 
}

void Joueur::deleteUnite(Unite * unite) {
    v_Unite.erase(unite->Getnom()); 
}
