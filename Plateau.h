#ifndef PLATEAU_H
#define PLATEAU_H

#include <iostream>
#include <string>
#include <QGraphicsScene>
#include <QProgressBar>
#include "Case.h"
#include "enumerations.h"
#include "Entite.h"

using namespace std;

class Plateau : public QGraphicsScene {
    Q_OBJECT
private :
        int m_hauteur;
        int m_largeur;
        Case*** plateau;
        QGraphicsItem* selected;
        flagsAppli flag;
        QProgressBar *pop;
        QProgressBar *PtAction;
        vector<Batiment *> v_Batiment;

private slots :
    void handleDep();

public :
        Plateau(string nomFichier="plateau1.data");
        Plateau(const Plateau& ) : QGraphicsScene(){}
        ~Plateau();

        inline Entite * getEntite(int x, int y) { return plateau[x][y]->getOccupant(); }
        // retourne null si pas d'unite ou si c'est un batiment
        inline Case * getCase(int x, int y) { return plateau[x][y]; }
        inline void ajoutBatiment(Batiment * bat) { v_Batiment.push_back(bat); }
        bool isFini(ifstream& fichier);
        void setSelect(QGraphicsItem* c);
        inline QGraphicsItem* getSelect() {return selected;}
        inline void setFlag(flagsAppli f) {flag=f;}
        inline flagsAppli getFlag() {return flag;}
};

#endif
