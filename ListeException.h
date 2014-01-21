#ifndef LISTEEXCEPTION_H
#define LISTEEXCEPTION_H

#include <exception>

using namespace std;

class ListeException : public exception
{
public:
    ListeException() {}
    const char * what() const throw () { return "Exception"; }
};

class FinDeJeu : public ListeException
{
public:
    FinDeJeu() {}
};

class ManquePtAction : public ListeException
{
public:
    ManquePtAction() {}
    const char * what() const throw () { return "Le joueur n'a pas assez de ptAction"; }
};

class ManquePopulation : public ListeException
{
public:
    ManquePopulation() {}
    const char * what() const throw () { return "Le joueur n'a pas assez de population"; }
};

class ManquePortee : public ListeException
{
public:
    ManquePortee() {}
    const char * what() const throw () { return "L'unite n'a pas assez de Portee"; }
};

class PtAction : public ListeException
{
public:
    PtAction() {}
    const char * what() const throw () { return "Erreur dans le comptage des points d'actions"; }
};

class Population : public ListeException
{
public:
    Population() {}
    const char * what() const throw () { return "Erreur dans le comptage des points de population"; }
};
#endif // LISTEEXCEPTION_H
