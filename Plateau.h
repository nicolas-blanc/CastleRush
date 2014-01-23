#ifndef PLATEAU_H
#define PLATEAU_H

#include <QLabel>
#include <iostream>
#include <string>
#include <QGraphicsScene>
#include <QProgressBar>
#include <QPushButton>

#include "Sort.h"
#include "enumerations.h"
#include "Case.h"

using namespace std;

class Tour;
class Entite;
class Batiment;
class Joueur;
class Attaque;
class Unite;
class Plateau : public QGraphicsScene {
    Q_OBJECT
private :
        int m_hauteur;
        int m_largeur;
        Case*** plateau;
        QGraphicsItem* selected;
        QGraphicsPixmapItem* background;
        flagsAppli flag;
        QProgressBar *pop;
        QProgressBar *PtAction;
        vector<Batiment *> v_Batiment;
        Joueur *jclient;
        Joueur *jserveur;
        QLabel *nom;
        QLabel *mvt;
        QLabel *atk;
        QLabel *por;
        QLabel *vie;

        vector<QPushButton*> v_sort;
        Sort * choixSort;

        QLabel *TOUR;

        QPushButton* att;
        QPushButton* sorts;
        QPushButton* dep;
        QPushButton* capt;
        QPushButton* annuler;
        QPushButton* fint;
        QPushButton* invoc;

        QPushButton* guer;
        QPushButton* arch;
        QPushButton* chev;
        QPushButton* vol;
        QPushButton* mag;
        QPushButton* pret;

        catUnite unitInvoc;

        vector<Joueur*> j;
        Joueur* jtour;

        int NombreTour;
        int NombreTourJoueur;
private slots :
    void gestionTour();
    void handleDep();
    void handleAtt();
    void handleSort();
    void handleChoixSort(int i);
    void intInvocGue();
    void intInvocArc();
    void intInvocChe();
    void intInvocMag();
    void intInvocPre();
    void intInvocVol();
public :
        Plateau(vector<Joueur*> joueurs, string nomPlateau = "plateau1.data");
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
        void updatePopPt();
        void afficheInfoUnite(Entite *u);
        void cacheInfoUnite();
        void InfoNull();
        void setBoutons(typeElement type, int numJoueur=0);
        void setBoutonsUnite(bool active);
        void highlight(Case* c, int portee=-1);
        void highlightAttaque(Case* c, int portee=0);
        vector<Case*> cheminDeplacement(Case* c1, Case* c2, int portee);
        bool porteeAttaquePossible(Case* c1, Case* c2, int portee);

        inline void setUnitInvoc(catUnite unite) { unitInvoc = unite;}
        inline catUnite getUnitInvoc() { return unitInvoc;}

        Joueur * getJoueurTour(){return jtour;}

        inline Sort* getChoixSort() { return choixSort; }

        void setNombreTour(int tour){NombreTour = tour;}
        int getNombreTour(){return NombreTour;}

        void setNombreTourJoueur(int tour){NombreTourJoueur = tour;}
        int getNombreTourJoueur(){return NombreTourJoueur;}
        Unite * getUniteAttaqueTour(Tour* tr);
};
#include "Tour.h"
#include "Entite.h"
#endif
