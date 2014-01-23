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
    vector<Unite*>::iterator it = v_Unite.begin();
    it = find(it,v_Unite.end(),u);
    v_Unite.erase(it);
}

void Joueur::deleteBatiment(Batiment*b)
{
    vector<Batiment*>::iterator it = v_Batiment.begin();
    it = find(it, v_Batiment.end(), b);
    v_Batiment.erase(it);
}
