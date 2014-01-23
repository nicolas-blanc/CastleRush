#ifndef BATIMENTBONUSSTAT_H
#define BATIMENTBONUSSTAT_H

#include <stdlib.h>
#include <vector>

#include "Batiment.h"

using namespace std;

class BatimentBonusStat : public Batiment
{
        private :
        int m_Stat;
        int m_Bonus;
        int m_NbTours;

    public :
        BatimentBonusStat(QGraphicsItem* parent, vector<Case*>& ensCase, string nom, int stat);
        inline int getStat() { return m_Stat;}
        inline void setStat(int Stat) { m_Stat = Stat;}
        inline int getBonus() { return m_Bonus; }
        inline void setBonus(int bonus) { m_Bonus = bonus;}
        inline int getNbTours() { return m_NbTours; }
        inline void setNbTours(int nbTours) { m_NbTours = nbTours; }
        inline int rand_a_b(int a, int b) { return rand()%(b-a) +a;}
        inline void miseAJourBonus();

        void modifBonus();
        // Modifie le bonus dans le vector de joueur, en fonction du bonus et du nombre de tours

        void Bonus();

        void randomStat();

        void changementProprio(Joueur *j);

protected:
      void mouseReleaseEvent(QGraphicsSceneMouseEvent *);

};

#endif // BATIMENTBONUSSTAT_H
