/*
 * File:   Pretre.h
 * Author: MouaHH
 *
 * Created on 21 décembre 2013, 14:45
 */

#ifndef PRETRE_H
#define        PRETRE_H

#include "Unite.h"

class Pretre : public Unite
{
    public:
    Pretre(QGraphicsItem * parent, Case* c, Joueur* j);
};


#endif        /* PRETRE_H */
