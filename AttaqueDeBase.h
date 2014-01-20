#ifndef ATTAQUEDEBASE_H
#define	ATTAQUEDEBASE_H

#include "Attaque.h"

class AttaqueDeBase : public Attaque {
public:

    AttaqueDeBase(int portee = 1);
    void lancerAttaque(Case* c);
};
#endif	/* ATTAQUEDEBASE_H */

