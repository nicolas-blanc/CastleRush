#include "Joueur.h"
#include "Batiment.h"
#include "Plateau.h"

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

void Joueur::deleteUnite(Unite*u)
{
    vector<Unite*>::iterator it;
    it = find(getUnite().begin(), getUnite().end(), u);
    getUnite().erase(it);
}

void Joueur::deleteBatiment(Batiment*b)
{
    vector<Batiment*>::iterator it;
    it = find(getBatiment().begin(), getBatiment().end(), b);
    getBatiment().erase(it);
}
