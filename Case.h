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

class Case : public QGraphicsRectItem, QObject {
private :
        Entite* m_occupant;
        bool m_batiment;
        vector<Effet*> m_effets;
        int m_x;
        int m_y;
        bool isSelected;
public :
        Case(int x, int y, QObject* parent);
        Case(const Case& ) : QGraphicsRectItem(),QObject() {cout<<"lol"<<flush;}
        //void paint(QPainter *painter, const QStyleOptionGraphicsItem *option,
        //           QWidget *widget);
        void setOccupant(Entite* occ, bool bat = false);
        inline Entite* getOccupant() {return m_occupant;}
        inline Entite* getUnite() { if (!(m_batiment)) return m_occupant; else return NULL; }
        void transmettreAttaque(int nbPV);
        bool isOccupee();
        void declencherEffets();
        Plateau* parent();

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
