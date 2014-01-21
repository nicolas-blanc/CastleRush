#ifndef PLATEAU_H
#define PLATEAU_H

#include <QLabel>
#include <iostream>
#include <string>
#include <QGraphicsScene>
#include <QProgressBar>
#include "Case.h"
#include "enumerations.h"
#include "Entite.h"
#include <QPushButton>

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
        Joueur *jclient;
        Joueur *jserveur;
        QLabel *nom;
        QLabel *mvt;
        QLabel *atk;
        QLabel *por;
        QLabel *vie;

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

        int unitInvoc;

private slots :
    void handleDep();
    void handleAtt();
    void intInvocGue();
    void intInvocArc();
    void intInvocChe();
    void intInvocMag();
    void intInvocPre();
    void intInvocVol();
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
        void update();
        void afficheInfoUnite(Entite *u);
        void cacheInfoUnite();
        void InfoNull();
        void allumerButtons();
        void eteindreButtons();
        void allumerButtonsBati();
        void eteindreButtonsBati();
        void highlight(Case* c, int portee=0);
        bool porteePossible(Case* c1, Case* c2, int portee);

        inline void setUnitInvoc(int i) { unitInvoc = i;cout<<"set : "<<unitInvoc<<flush;}
        inline int getUnitInvoc() { cout<<"get : "<<unitInvoc<<endl<<flush; return unitInvoc;}
        void uniteInvocable();
        void deleteUniteInvocable();
};

#endif
