#include "Joueur.h"

Joueur::Joueur(int couleur, int numero) : m_listeBonusJoueur() {
    m_couleur = couleur;
    m_numero = numero;

    for (unsigned int i=0; i<6; i++)
        m_listeBonusJoueur.push_back(0);
    setPtActionMax(20);
    setPtAction(20);
    setPopulationMax(5);
    setPopulation(0);

}

Joueur::~Joueur() {
}

void Joueur::setBatiment(Batiment * batiment) { 
    v_Batiment.push_back(batiment);
}

void Joueur::setUnite(Unite * unite) {
    v_Unite.push_back(unite);
}

void Joueur::deleteBatiment(Batiment* bat) {
    vector<Batiment*>::iterator it = v_Batiment.begin();
    int i = 0;
    while(v_Batiment[i] != bat)
    { i++; it++; }

    v_Batiment.erase(it);
}

void Joueur::deleteUnite(Unite * unite) {
    vector<Unite*>::iterator it = v_Unite.begin();
    int i = 0;
    while(v_Unite[i] != unite)
    { i++; it++; }

    v_Unite.erase(it);
}
