#ifndef BATIMENT_H
#define	BATIMENT_H

#include <vector>

#include "Entite.h"
#include "Joueur.h"

using namespace std;

class Batiment : public Entite {
public:
    Batiment(QGraphicsItem *parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax);
    Batiment(QGraphicsItem *parent, Case* c, Joueur* j, string nom, int vieMin, int vieMax);
};
#endif	/* BATIMENT_H */

