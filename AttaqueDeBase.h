#ifndef ATTAQUEDEBASE_H
#define	ATTAQUEDEBASE_H

#include "Attaque.h"

class AttaqueDeBase : public Attaque {
public:

    AttaqueDeBase(int portee = 1);
    AttaqueDeBase(int portee, int deg);
    void lancerAttaque(Case* c);
};
#endif	/* ATTAQUEDEBASE_H */

