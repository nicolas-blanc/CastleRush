#ifndef CASE_H
#define CASE_H

#include <iostream>
#include <string>
#include <vector>
#include <QGraphicsItem>
#include <QPainter>


using namespace std;

class Entite;
class Unite;
class Effet;
class Plateau;
class Joueur;

class Case : public QGraphicsRectItem, QObject {
private :
        Entite* m_occupant;
        bool m_batiment;
        vector<Effet*> m_effets;
        int m_x;
        int m_y;
        bool isSelected;
        bool glyphe;
public :
        Case(int x, int y, QObject* parent);
        Case(const Case& ) : QGraphicsRectItem(),QObject() {}
        //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        //           QWidget *widget);
        void setOccupant(Entite* occ, bool bat = false);
        inline Entite* getOccupant() {return m_occupant;}
        inline Entite* getUnite() { if (!(m_batiment)) return m_occupant; else return NULL; }
        void transmettreAttaque(int nbPV);
        bool isOccupee();
        void declencherEffets();
        Plateau* parent();
        bool getGlyphe() {return glyphe;}
        void setGlyphe(bool s) {glyphe = s;}
        void declencherEffets(Joueur *joueur);

        inline void ajouterEffet(Effet * effet) { m_effets.push_back(effet); }
        void enleverEffet(vector<Effet*>::iterator it) { m_effets.erase(it); }
        inline bool isEffets() { return m_effets.size() == 0; }

        Case& operator=(const Case& ) {return *this;}

        inline int getX() { return m_x; }
        inline int getY() { return m_y; }

protected :
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
};

#include "Entite.h"
#include "Unite.h"
#include "Effet.h"

#endif
