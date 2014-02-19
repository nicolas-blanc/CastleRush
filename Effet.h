#ifndef EFFET_H
#define	EFFET_H

class Joueur;
class Case;

class Effet {
    private :
        int m_nbTour;
        Joueur * m_joueur;
    public :
        Effet(Joueur * joueur,int tour);
        bool decreaseTour();
        inline Joueur * getJoueur() { return m_joueur; }

        virtual void appliquerEffetUnite(Case * ) {}
        void appliquerEffetCase(Case *c);
        void enleverEffetUnite(Case *c){}
};

class DegenVie : public Effet {
public:
    DegenVie(Joueur * joueur,int nbTour, int malus);
    void appliquerEffetUnite(Case *c);
    void enleverEffetUnite(Case *){}
private:
    int m_malus;
};

class MalusMouvement : public Effet {
public:
    MalusMouvement(Joueur * joueur,int nbTour, int malus);
    void appliquerEffetUnite(Case *c);
    void enleverEffetUnite(Case *c);
private:
    int m_malus;
};

class BonusDegat : public Effet {
public:
    BonusDegat(Joueur *joueur, int nbTour, int bonus);
    void appliquerEffetUnite(Case *c);
    void enleverEffetUnite(Case *c);
private:
    int m_bonus;
};
#include "Case.h"

#endif	/* EFFET_H */

