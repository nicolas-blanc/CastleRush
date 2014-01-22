/*
 * File:   Chateau.h
 * Author: MouaHH
 *
 * Created on 21 décembre 2013, 14:26
 */

#ifndef CHATEAU_H
#define	CHATEAU_H

#include "Batiment.h"
#include "Unite.h"
#include "Guerrier.h"
#include "Archer.h"
#include "Chevalier.h"
#include "Magicien.h"
#include "Pretre.h"
#include "Voleur.h"
#include "enumerations.h"

class Chateau : public Batiment
{
    public:
    Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, Joueur* j, string nom);
    Chateau(QGraphicsItem* parent, vector<Case*>& EnsCase, string nom);
    bool Invoquer(catUnite unite, Case* c);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#endif	/* CHATEAU_H */

