#ifndef ARCHER_H
#define        ARCHER_H

#include "Unite.h"

class Archer : public Unite
{
    public:
    Archer(QGraphicsItem * parent, Case* c, Joueur* j);
};
#endif        /* ARCHER_H */
