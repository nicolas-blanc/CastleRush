#ifndef ENTITE_H
#define ENTITE_H

#include <string>
#include <iomanip>
#include <vector>
#include <QGraphicsPixmapItem>

#include "PointDeVie.h"

using namespace std;

class Attaque;
class Case;
class Joueur;

class Entite : public QGraphicsPixmapItem
{
    public:
        Entite(QGraphicsItem * parent, vector<Case*>& ensCase, Joueur* j, string nom, int vieMin, int vieMax);
        Entite(QGraphicsItem * parent, vector<Case*>& ensCase, string nom, int vieMin, int vieMax);
        virtual ~Entite();
        inline string Getnom() { return m_nom; }
        inline void Setnom(string val) { m_nom = val; }
        inline int getVie() { return m_vie.GetValeur(); }
        inline void setVie(int val) { m_vie.modifVie(val); }
        inline vector<Case*> getPosition() { return m_position; }
        void setPosition(vector<Case*> position);
        inline void setJoueur(Joueur* j) {m_Joueur=j;}
        inline Joueur* getJoueur() {return m_Joueur;}
        void modifierVie(int vie);
        inline bool estMort() { return m_vie.GetValeur() == 0;}
        bool adjacent(Case* c);

//        int& operator[] (unsigned int i) { return m_position[i]; };
    protected:
        string m_nom;
        PointDeVie m_vie;
        vector<Case*> m_position;
        Joueur* m_Joueur;
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#include "Attaque.h"
#include "Case.h"
#include "Joueur.h"

#endif // ENTITE_H
