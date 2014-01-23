#ifndef ATTAQUEDEBASE_H
#define	ATTAQUEDEBASE_H

#include "Attaque.h"
#include "Case.h"

class AttaqueDeBase : public Attaque {
public:

    AttaqueDeBase(int portee = 1, Entite* ent = NULL);
    AttaqueDeBase(int portee, int deg, Entite* ent = NULL);
    void lancerAttaque(Case* c);
    void animationAttaque(Case* c1, Case* c2);
};
#endif	/* ATTAQUEDEBASE_H */

