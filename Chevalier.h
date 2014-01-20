/* 
 * File:   Chevalier.h
 * Author: MouaHH
 *
 * Created on 21 décembre 2013, 14:45
 */

#ifndef CHEVALIER_H
#define	CHEVALIER_H

#include "Unite.h"

class Chevalier : public Unite
{
    public:
    Chevalier(QGraphicsItem * parent, Case* c, Joueur* j);
};



#endif	/* CHEVALIER_H */

