#ifndef UNITE_H
#define UNITE_H

#include "Entite.h"
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
    Q_PROPERTY ( QPointF offsetAtk READ getMyOffsetAtk WRITE setMyOffsetAtk)
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
        Sort* getSort(int sort);
        inline map <string,Sort*> getSort() { return v_sort; }
        virtual void initSort() {}
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

        bool deplacer(Case* c);
        bool attaquer(Case* c, Attaque* attaque);
        bool attaquer(Case* c);
        void modifierVie(int vie);

        inline void modifBonus(int bonus, int effet) { v_bonus[bonus] = effet; }
        inline vector<int> getBonusUnite() { return v_bonus; }

        inline void ajouterEffet(Effet* effet) { this->v_effet.push_back(effet); }
        void enleverEffet(Effet* effet);
        int mouvementDemande(Case* c);

        vector<QPixmap*> getImageFace() { return v_dep_face; }
        vector<QPixmap*> getImageGauche() { return v_dep_gauche; }
        vector<QPixmap*> getImageDroite() { return v_dep_droite; }
        vector<QPixmap*> getImageDos() { return v_dep_dos; }
        vector<QPixmap*> getImageAttaque() { return v_attaque; }

        void setImageFace(QPixmap* im) { v_dep_face.push_back(im); }
        void setImageGauche(QPixmap* im) { v_dep_gauche.push_back(im); }
        void setImageDroite(QPixmap* im) { v_dep_droite.push_back(im); }
        void setImageDos(QPixmap* im) { v_dep_dos.push_back(im); }
        void setImageAttaque(QPixmap* im) { v_attaque.push_back(im); }
        void animationDeplacement(vector<Case*> chemin);
        void animationAttaque(Case* c1, Case* c2);

        void attaquer(Entite* e);
        void attaquer(Entite* e, Attaque* a);

        QPointF getMyOffset() const {return this->offset();}
        Q_SLOT void setMyOffset(QPointF off) {this->setOffset(off.x(),off.y());}
        int getMyPixmap() const {return 0;}
        Q_SLOT void setMyPixmap(int pm) {if (pm<10) this->setPixmap(*v_dep_face[pm%4]); else if (pm<20) this->setPixmap(*v_dep_dos[(pm-10)%4]); else if (pm<30) this->setPixmap(*v_dep_gauche[(pm-20)%4]); else if (pm<40) this->setPixmap(*v_dep_droite[(pm-30)%4]); else if (pm<50) atk.setPixmap(*v_attaque[(pm-40)%v_attaque.size()]); else if (pm==50) atk.setPixmap(QPixmap(""));}
        QPointF getMyOffsetAtk() const {return atk.offset();}
        Q_SLOT void setMyOffsetAtk(QPointF off) {atk.setOffset(off.x()-7,off.y()-7);}

    protected:
        string m_nom;
        unsigned int m_mouvement;
        unsigned int m_cout;
        unsigned int m_population;
        AttaqueDeBase* m_AttaqueParDefaut;
        map <string,Sort*> v_sort;
        vector <Effet*> v_effet;
        vector<int> v_bonus;
            /* 0 - point de vie
             * 1 - degat
             * 2 - portée
             * 3 - mouvement
             * 4 - Invisble
             * 5 - Paralysie
             */

        void setAttaqueDeBase(int portee = 1);
        vector <QPixmap*> v_dep_face;
        vector <QPixmap*> v_dep_gauche;
        vector <QPixmap*> v_dep_droite;
        vector <QPixmap*> v_dep_dos;
        vector <QPixmap*> v_attaque;

        QGraphicsPixmapItem atk;
    private:
        //inline int getDepX(Case c) { int dep = c.getX() - Entite::getPosition()[0].getX(); return abs(dep); };
        //inline int getDepY(Case c) { int dep = c.getY() - Entite::getPosition()[0].getY(); return abs(dep); };
};
#include "AttaqueDeBase.h"
#include "Sort.h"
#include "Effet.h"

#endif // UNITE_H
