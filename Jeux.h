#ifndef JEUX_H
#define JEUX_H

#include <vector>

#include "Plateau.h"
#include "Joueur.h"
#include "ListeException.h"

using namespace std;

class Jeux
{
    public:
        Jeux(int nbrJoueur, string nomPlateau);
        virtual ~Jeux();
        inline int getnbTour() { return m_nbTour; }
        inline void setnbTour(int val) { m_nbTour = val; }
        inline int getnbJoueur() { return m_nbJoueur; }

        void afficherGraphiqueConsole();
        void partieConsole();

        bool testFinDeJeu();

        void afficherInfos(Unite * unite);
    protected:
    private:
        bool m_FinDePartie;
        int m_nbTour;
        int m_nbJoueur;

        vector <Joueur*> m_Joueur;
        Plateau* m_Plateau;
};

#endif // JEUX_H
