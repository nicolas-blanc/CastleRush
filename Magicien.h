/*
 * File:   Magicien.h
 * Author: MouaHH
 *
 * Created on 21 décembre 2013, 14:45
 */

#ifndef MAGICIEN_H
#define	MAGICIEN_H

#include "Unite.h"

class Magicien : public Unite
{
    public:
    Magicien(QGraphicsItem * parent, Case* c, Joueur* j);
};


#endif	/* MAGICIEN_H */

