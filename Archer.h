#ifndef ARCHER_H
#define        ARCHER_H

#include "Unite.h"

class Archer : public Unite
{
    public:
    Archer(QGraphicsItem * parent, Case* c, Joueur* j);
    void initSort();
};
#endif        /* ARCHER_H */
