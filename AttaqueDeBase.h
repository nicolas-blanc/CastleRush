#ifndef ATTAQUEDEBASE_H
#define	ATTAQUEDEBASE_H

#include "Attaque.h"
#include "Case.h"

class AttaqueDeBase : public Attaque {
public:
    AttaqueDeBase(Entite *entite,int portee, int deg);
    void lancerAttaque(Case* c);
};
#endif	/* ATTAQUEDEBASE_H */

