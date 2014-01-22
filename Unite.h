#ifndef UNITE_H
#define UNITE_H

#include "Entite.h"
#include "Effet.h"
#include "Attaque.h"
#include "Case.h"


#include <vector>
#include <cmath>
#include <map>
#include <QGraphicsItemAnimation>

using namespace std;

class AttaqueDeBase;
class Sort;
class Effet;
class Unite : public QObject,public Entite {
    Q_OBJECT
    Q_PROPERTY ( QPointF offset READ getMyOffset WRITE setMyOffset)
    Q_PROPERTY ( int pixmap READ getMyPixmap WRITE setMyPixmap)
    public:
        Unite(QGraphicsItem * parent, unsigned int mvt, unsigned int ct, unsigned int pop, int vieMax, int vieMin, Case* c, Joueur* j, string nom);
        virtual ~Unite();
        int getMouvement();
        inline void setMouvement(int val) { if (val >= 0) m_mouvement = val; } // a modif exception
        inline int getCout() { return m_cout; }
        inline void setCout(int val) { if (val >= 0) m_cout = val; } // a modif exception
        inline int getPopulation() { return m_population; }
        inline void setPopulation(int val) { if (val >= 0) m_population = val; } // a modif exception
        inline AttaqueDeBase* getAttaqueParDefaut() { return m_AttaqueParDefaut; }
        inline Sort* getSort(string nomSort) { return v_sort[nomSort]; }
        virtual void initSort();
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        void deplacer(Case* c);
        bool deplacementPossible(Case* c); // /!\ a corriger avec getDepX et getDepY
        bool attaquer(Case* c, Attaque* attaque);
        bool attaquer(Case* c);
        void modifierVie(int vie);

        inline void insererEffet(Effet* effet) { this->v_effet.push_back(effet); }
        void enleverEffet(Effet* effet);
        int mouvementDemande(Case* c);

        vector<QPixmap*> getImageFace() { return v_dep_face; }
        vector<QPixmap*> getImageGauche() { return v_dep_gauche; }
        vector<QPixmap*> getImageDroite() { return v_dep_droite; }
        vector<QPixmap*> getImageDos() { return v_dep_dos; }

        void setImageFace(QPixmap* im) { v_dep_face.push_back(im); }
        void setImageGauche(QPixmap* im) { v_dep_gauche.push_back(im); }
        void setImageDroite(QPixmap* im) { v_dep_droite.push_back(im); }
        void setImageDos(QPixmap* im) { v_dep_dos.push_back(im); }
        void animationDeplacement(vector<Case*> chemin);

        void attaquer(Entite* e);
        void attaquer(Entite* e, Attaque* a);

        QPointF getMyOffset() const {return this->offset();}
        Q_SLOT void setMyOffset(QPointF off) {this->setOffset(off.x(),off.y());}
        int getMyPixmap() const {return 0;}
        Q_SLOT void setMyPixmap(int pm) {if (pm<10) this->setPixmap(*v_dep_face[pm%4]); else if (pm<20) this->setPixmap(*v_dep_dos[(pm-10)%4]); else if (pm<30) this->setPixmap(*v_dep_gauche[(pm-20)%4]); else if (pm<40) this->setPixmap(*v_dep_droite[(pm-30)%4]);}

    protected:
        string m_nom;
        unsigned int m_mouvement;
        unsigned int m_cout;
        unsigned int m_population;
        AttaqueDeBase* m_AttaqueParDefaut;
        map <string,Sort*> v_sort;
        vector <Effet*> v_effet;

        vector <QPixmap*> v_dep_face;
        vector <QPixmap*> v_dep_gauche;
        vector <QPixmap*> v_dep_droite;
        vector <QPixmap*> v_dep_dos;
    private:
        //inline int getDepX(Case c) { int dep = c.getX() - Entite::getPosition()[0].getX(); return abs(dep); };
        //inline int getDepY(Case c) { int dep = c.getY() - Entite::getPosition()[0].getY(); return abs(dep); };
        void setAttaqueDeBase();
};
#include "AttaqueDeBase.h"
#include "Sort.h"
#include "Effet.h"

#endif // UNITE_H
