#ifndef ATTAQUE_H
#define	ATTAQUE_H

#include <iostream>
#include <string>
#include <QObject>
#include <QGraphicsPixmapItem>

using namespace std;

class Case;
class Entite;

class Attaque : public QObject {
    Q_OBJECT
    Q_PROPERTY ( QPointF offsetAtk READ getMyOffsetAtk WRITE setMyOffsetAtk)
    Q_PROPERTY ( int pixmap READ getMyPixmap WRITE setMyPixmap)
protected:
    int m_Degat;
    int m_Portee;
    int m_PtAction;
    Entite * m_Entite;
    vector <QPixmap*> v_attaque;
    QGraphicsPixmapItem atk;
    
public:
    Attaque(int portee, int degat = 1, int ptAction = 1, Entite* ent = NULL);
    inline void setDegat(int degat) { m_Degat = degat;}
    int getDegat();
    inline void setPortee(int portee) { m_Portee = portee; }
    int getPortee();
    inline void setPtAction(int ptAction) { m_PtAction = ptAction; }
    inline int getPtAction() { return m_PtAction; }

    void setImageAttaque(QPixmap* im) { v_attaque.push_back(im); }
    vector<QPixmap*> getImageAttaque() { return v_attaque; }
    virtual void animationAttaque(Case*, Case*) {}
    QPointF getMyOffsetAtk() const {return atk.offset();}
    Q_SLOT void setMyOffsetAtk(QPointF off) {atk.setOffset(off.x()-7,off.y()-7);}
    int getMyPixmap() const {return 0;}
    Q_SLOT void setMyPixmap(int pm) {if (pm>=0){ atk.setPixmap(*v_attaque[pm%v_attaque.size()]);} else if (pm==-1) atk.setPixmap(QPixmap(""));}

    virtual void lancerAttaque(Case* c);
    void Attaquer();
    void lierEntite(Entite* ent) { m_Entite = ent; }
};


#endif	/* ATTAQUE_H */

