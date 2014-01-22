#ifndef TOUR_H
#define TOUR_H

#include "Batiment.h"
#include "AttaqueDeBase.h"
#include "Attaque.h"

class Tour : public Batiment
{
    private :
        AttaqueDeBase *m_attaque;
        void setAttaqueDeBase();

    public :
        Tour(QGraphicsItem* parent, Case* c, Joueur* j, string nom);
        Tour(QGraphicsItem* parent, Case* c, string nom);
        void attaquer(Case* c);
        inline AttaqueDeBase *getAttaque(){return m_attaque;}
        inline void setAtttaque(AttaqueDeBase *atk){m_attaque = atk;}
        void attaqueAuto();
protected:
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#endif        /* TOUR_H */
