#ifndef SORT_H
#define	SORT_H

#include <string>

#include "Attaque.h"

class Effet;

using namespace std;

class Sort : public Attaque {
public:
    Sort(Entite * entite,string nom, int degat = 1, int portee = 1, int ptAction = 1);
    virtual void lancerAttaque(Case* c);
    inline string getNom() { return m_nomSort; }
private:
    string m_nomSort;
};

class AttaquePuissante : public Sort {
public:
    AttaquePuissante(Entite * entite,string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class Charge : public Sort {
public:
    Charge(Entite * entite,string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class AttaqueEmpoisonnee : public Sort {
public:
    AttaqueEmpoisonnee(Entite * entite,string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    Effet * m_effet;
};

class GlypheGel : public Sort {
public:
    GlypheGel(Entite * entite,string nom, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    Effet * m_effet;
};

class Soin : public Sort {
public:
    Soin(Entite * entite,string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
};

class Concentration : public Sort {
public:
    Concentration(Entite * entite,string nom, int degat, int portee, int ptAction);
    void lancerAttaque(Case * c);
private:
    Effet * m_effet;
};

#endif	/* SORT_H */

