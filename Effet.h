#ifndef EFFET_H
#define	EFFET_H


class Case;

class Effet {
    private :
        int m_nbTour;
    public :
        Effet(int tour);
        bool decreaseTour();

        virtual void appliquerEffetUnite(Case * c) {}
        void appliquerEffetCase(Case *c);
};

class DegenVie : public Effet {
public:
    DegenVie(int nbTour, int malus);
    void appliquerEffetUnite(Case *c);
private:
    int m_malus;
};

class MalusMouvement : public Effet {
public:
    MalusMouvement(int nbTour, int malus);
    void appliquerEffetUnite(Case *c);
private:
    int m_malus;
};

class BonusDegat : public Effet {
public:
    BonusDegat(int nbTour, int bonus);
    void appliquerEffetUnite(Case * c);
private:
    int m_bonus;
};
#include "Case.h"

#endif	/* EFFET_H */

