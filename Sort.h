#ifndef SORT_H
#define	SORT_H

#include <string>

#include "Attaque.h"
#include "Effet.h"

using namespace std;

class Sort : public Attaque {
public:
    Sort(string nom, int degat = 1, int portee = 1, int ptAction = 1);
    virtual void lancerAttaque(Case* c);
    inline string getNom() { return m_nomSort; }
private:
    string m_nomSort;
};

class AttaquePuissante : public Sort {
public:
    AttaquePuissante(string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class Charge : public Sort {
public:
    Charge(string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class AttaqueEmpoisonnee : public Sort {
public:
    AttaqueEmpoisonnee(string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    DegenVie * m_effet;
};

class GlypheGel : public Sort {
public:
    GlypheGel(string nom, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    MalusMouvement * m_effet;
};

class Soin : public Sort {
public:
    Soin(string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class Concentration : public Sort {
public:
    Concentration(string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    BonusDegat * m_effet;
};

#endif	/* SORT_H */

