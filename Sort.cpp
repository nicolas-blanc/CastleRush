#include "Sort.h"
#include "Plateau.h"

Sort::Sort(Entite *entite, string nom, int degat, int portee, int ptAction) : Attaque(entite,portee,degat,ptAction) {
    m_nomSort = nom;
}

void Sort::lancerAttaque(Case *c) {}

AttaquePuissante::AttaquePuissante(Entite *entite, string nom, int degat, int portee, int ptAction) : Sort(entite,nom,degat,portee,ptAction) {}

void AttaquePuissante::lancerAttaque(Case *c) {
    c->transmettreAttaque(this->getDegat());
}

Charge::Charge(Entite *entite, string nom, int degat, int portee, int ptAction) : Sort(entite,nom,degat,portee,ptAction) {}

void Charge::lancerAttaque(Case *c) {
    int x = m_Entite->getPosition()[0]->getX() - c->getX();
    int y = m_Entite->getPosition()[0]->getY() - c->getY();

    c->transmettreAttaque(this->getDegat());
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()+x,c->getY()+y)->transmettreAttaque(this->getDegat());
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()+(2*x),c->getY()+(2*y))->transmettreAttaque(this->getDegat());
}

AttaqueEmpoisonnee::AttaqueEmpoisonnee(Entite *entite, string nom, int degat, int portee, int ptAction) : Sort(entite,nom,degat,portee,ptAction) {
    m_effet = new DegenVie(2,1);
}

void AttaqueEmpoisonnee::lancerAttaque(Case *c) {
    cout<<"test"<<flush;
    cout<<"degat "<<flush<<this->getDegat()<<flush;
    c->transmettreAttaque(this->getDegat());
    ((Unite*) c->getUnite())->ajouterEffet(m_effet);
}

GlypheGel::GlypheGel(Entite *entite, string nom, int portee, int ptAction) : Sort(entite,nom,portee,0,ptAction) {
    m_effet = new MalusMouvement(3,2);
}

void GlypheGel::lancerAttaque(Case *c) {
    c->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()-1,c->getY())->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()-1,c->getY()-1)->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX(),c->getY()-1)->ajouterEffet(m_effet);
}

Soin::Soin(Entite *entite, string nom, int degat, int portee, int ptAction) : Sort(entite,nom,degat,portee,ptAction) {}

void Soin::lancerAttaque(Case *c) {
    c->transmettreAttaque(this->getDegat());
}

Concentration::Concentration(Entite *entite, string nom, int degat, int portee, int ptAction) : Sort(entite,nom,degat,portee,ptAction) {
    m_effet = new BonusDegat(2,1);
}

void Concentration::lancerAttaque(Case *c) {
    ((Unite*) c->getUnite())->ajouterEffet(m_effet);
}
