#ifndef UNITE_H
#define UNITE_H

#include "Entite.h"
#include "Effet.h"
#include "Attaque.h"
#include "Case.h"


#include <vector>
#include <cmath>
#include <map>

using namespace std;

class AttaqueDeBase;
class Sort;
class Effet;
class Unite : public Entite {
    public:
        Unite(QGraphicsItem * parent, unsigned int mvt, unsigned int ct, unsigned int pop, int vieMax, int vieMin, Case* c, Joueur* j, string nom);
        virtual ~Unite();
        int getMouvement();
        inline void setMouvement(int val) { if (val >= 0) m_mouvement = val; } // a modif exception
        inline int getCout() { return m_cout; }
        inline void setCout(int val) { if (val >= 0) m_cout = val; } // a modif exception
        inline int getPopulation() { return m_population; }
        inline void setPopulation(int val) { if (val >= 0) m_population = val; } // a modif exception
        inline AttaqueDeBase* getAttaqueParDefaut() { return m_AttaqueParDefaut; }
        inline Sort* getSort(string nomSort) { return v_sort[nomSort]; }
        virtual void initSort();
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        void deplacer(Case* c);
        bool deplacementPossible(Case* c); // /!\ a corriger avec getDepX et getDepY
        void attaquer(Case* c, Attaque* attaque);
        void attaquer(Case* c);
        void modifierVie(int vie);

        inline void insererEffet(Effet* effet) { this->v_effet.push_back(effet); }
        void enleverEffet(Effet* effet);

    protected:
        string m_nom;
        unsigned int m_mouvement;
        unsigned int m_cout;
        unsigned int m_population;
        AttaqueDeBase* m_AttaqueParDefaut;
        map <string,Sort*> v_sort;
        vector <Effet*> v_effet;

    private:
        //inline int getDepX(Case c) { int dep = c.getX() - Entite::getPosition()[0].getX(); return abs(dep); };
        //inline int getDepY(Case c) { int dep = c.getY() - Entite::getPosition()[0].getY(); return abs(dep); };
        void setAttaqueDeBase();
};
#include "AttaqueDeBase.h"
#include "Sort.h"
#include "Effet.h"

#endif // UNITE_H
