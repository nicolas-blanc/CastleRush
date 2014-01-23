#ifndef MAGICIEN_H
#define        MAGICIEN_H

#include "Unite.h"

class Magicien : public Unite
{
    public:
    Magicien(QGraphicsItem * parent, Case* c, Joueur* j);
    void initSort();
};


#endif        /* MAGICIEN_H */
