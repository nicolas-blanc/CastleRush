#ifndef BATIMENT_H
#define BATIMENT_H

#include <vector>

using namespace std;

class Entite;
class Joueur;

class Batiment : public Entite {
public:
    Batiment(QGraphicsItem *parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax);
    Batiment(QGraphicsItem * parent, vector<Case*>& ensCase, string nom, int vieMin, int vieMax);
    Batiment(QGraphicsItem *parent, Case* c, Joueur* j, string nom, int vieMin, int vieMax);
    Batiment(QGraphicsItem *parent, Case *c, string nom, int vieMin, int vieMax);
protected:
      void mouseReleaseEvent(QGraphicsSceneMouseEvent *);
};

#include "Entite.h"
#include "Joueur.h"

#endif        /* BATIMENT_H */
