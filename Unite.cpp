#include "Unite.h"
#include "ListeException.h"
#include "Plateau.h"
#include <exception>
#include <QMessageBox>
#include <math.h>
#include <QTimeLine>
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>
#include <QParallelAnimationGroup>

#define min(a,b) ((a)<(b)?(a):(b))
#define SIZE 36


Unite::Unite(QGraphicsItem * parent, unsigned int mvt, unsigned int ct, unsigned int pop, int vieMax, int vieMin, Case* c, Joueur* j, string nom)
: QObject(), Entite(parent, *new vector<Case*>(1,c),j,nom,vieMin,vieMax), atk(), v_dep_face(), v_dep_gauche(), v_dep_droite(), v_dep_dos() {
    this->setMouvement(mvt);
    this->setCout(ct);
    this->setPopulation(pop);
    for (unsigned int i=0; i<6; i++)
         v_bonus.push_back(0);
    j->setUnite(this);

    QPixmap* atq = new QPixmap("images/Attack5-2.png");
    for (int i=0; i<5; i++)
        this->setImageAttaque(new QPixmap(atq->copy(50*i,0,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(0,50,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(50,50,50,50)));
    ((Case*)parentItem())->parent()->addItem(&atk);
}

void Unite::setAttaqueDeBase(Entite * entite,int portee,int degat) {
    m_AttaqueParDefaut = new AttaqueDeBase(entite,portee,degat);
}

void Unite::animationDeplacement(vector<Case *> chemin ) {
    this->setSelected(false);
     float decalageX,decalageY;
     Case* caseActu=chemin[0];
     QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
     QSequentialAnimationGroup *animPm = new QSequentialAnimationGroup();
     QParallelAnimationGroup *groupPara = new QParallelAnimationGroup();

     QPointF OS = offset();
     int anim;
     int j=1;

     for (unsigned int i=1;i<chemin.size(); i++) {
         QPropertyAnimation *animation = new QPropertyAnimation(this, "offset");
         animation->setDuration(200);

         decalageX = (chemin[i]->getX()-caseActu->getX())*SIZE;
         decalageY = (chemin[i]->getY()-caseActu->getY())*SIZE;

         if (decalageX>0)
             anim=30;
         else if (decalageX<0)
             anim=20;
         else if (decalageY<0)
             anim=10;
         else if (decalageY>0)
             anim=0;

         QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
         animPix->setDuration(200);
         animPix->setStartValue(anim);
         animPix->setEndValue(anim+7);
         animPm->addAnimation(animPix);

         animation->setStartValue(OS);
         OS=QPointF(OS.x()+decalageX,OS.y()+decalageY);
         animation->setEndValue(OS);
         group->addAnimation(animation);

         j++;
         caseActu=chemin[i];
     }

     groupPara->addAnimation(group);
     groupPara->addAnimation(animPm);
     groupPara->start();
     this->setSelected(true);
}

bool Unite::deplacer(Case* c) {
    int mvt = this->mouvementDemande(c);
    vector<Case*> chemin=((Case*)this->parentItem())->parent()->cheminDeplacement(getPosition()[0],c,min((getMouvement()+getJoueur()->getListeBonusJoueur()[5]),(getJoueur()->getPtAction()+getJoueur()->getListeBonusJoueur()[1])));
    if(chemin[chemin.size()-1]!=NULL)
    {
        if(this->getJoueur()->getPtAction()-mvt >=0)
        {
            animationDeplacement(chemin);
            vector<Case*> position;
            position.push_back(c);
            this->setPosition(position);
            this->getJoueur()->modifPtAction(mvt);
            ((Plateau*)((Case*)this->parentItem())->parent())->setFlag(attente);
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

int Unite::mouvementDemande(Case* c)
{
    return abs(c->getX()-this->getPosition()[0]->getX())+abs(c->getY()-this->getPosition()[0]->getY());
}

void Unite::modifierVie(int vie) {
    Entite::modifierVie(vie);/*
    if (estMort())
        this->getJoueur()->deleteUnite(this);*/
}

void Unite::animationAttaque(Case* c1, Case* c2) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
    float decalageX = (c2->getX()-c1->getX())*SIZE/2;
    float decalageY = (c2->getY()-c1->getY())*SIZE/2;

    QPropertyAnimation *setoff = new QPropertyAnimation(this, "offsetAtk");
    setoff->setDuration(1);
    setoff->setStartValue(QPointF(offset().x()+decalageX,offset().y()+decalageY));
    setoff->setEndValue(QPointF(offset().x()+decalageX,offset().y()+decalageY));
    group->addAnimation(setoff);

    QPropertyAnimation *placement = new QPropertyAnimation(this, "pixmap");
    placement->setDuration(1);
    int anim;
    if (decalageX>0)
        anim=30;
    else if (decalageX<0)
        anim=20;
    else if (decalageY<0)
        anim=10;
    else if (decalageY>0)
        anim=0;
    placement->setStartValue(anim+1);
    placement->setEndValue(anim+1);
    group->addAnimation(placement);

    for (int i=0; i<2; i++) {
        QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
        animPix->setDuration(200);
        animPix->setStartValue(40);
        animPix->setEndValue(50);
        group->addAnimation(animPix);
    }


    group->start();
}

bool Unite::attaquer(Case* c, AttaqueDeBase *attaque) {
    bool attaquer;
    if(c->getOccupant()->getJoueur()!= ((Case*)parentItem())->parent()->getJoueurTour())
    {
        if (getJoueur()->getPtAction()<attaque->getPtAction()) {
            cout << "erreur PtAction" << flush;
            attaquer = false;
        }
        else if ((abs(c->getX() - this->getPosition()[0]->getX()) + abs(c->getY() - this->getPosition()[0]->getY())) > attaque->getPortee()) {
           cout << "erreur Portee," <<flush;
           attaquer = false;
        }
        else
        {
            animationAttaque(m_position[0], c);
            attaque->lancerAttaque(c);
            if (((c->getOccupant())->getVie())==0){
                QPixmap *tombe;
                tombe=new QPixmap("images/Coffin.png");
                (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));

                c->getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
                c->setOccupant(NULL);
            }
            this->getJoueur()->modifPtAction(this->getCout());
            attaquer = true;
        }
    }
    else
    {
        cout << "erreur Attaque Perso" << flush;
        attaquer = false;
    }
    return attaquer;
}

bool Unite::attaquer(Case* c, Sort* attaque) {
    bool attaquer;
    bool sortSoiMeme = (attaque->getNom() == "Concentration" || attaque->getNom() == "Soin");
    if(c->getOccupant()->getJoueur()!= ((Case*)parentItem())->parent()->getJoueurTour() || attaque->getDegat() < 0 || sortSoiMeme)
    {
        if (getJoueur()->getPtAction()<attaque->getPtAction()) {
            cout << "erreur PtAction" << flush;
            attaquer = false;
        }
        else if ((abs(c->getX() - this->getPosition()[0]->getX()) + abs(c->getY() - this->getPosition()[0]->getY())) > attaque->getPortee()) {
           cout << "erreur Portee," <<flush;
           attaquer = false;
        }
        else
        {
            attaque->lancerAttaque(c);
            cout<<"test2"<<flush;
            if (((c->getOccupant())->getVie())==0){
                QPixmap *tombe;
                tombe=new QPixmap("images/Coffin.png");
                (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));

                c->getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
                c->setOccupant(NULL);
            }
            this->getJoueur()->modifPtAction(this->getCout());
            attaquer = true;
        }
    }
    else
    {
        cout << "erreur Attaque Perso" << flush;
        attaquer = false;
    }
    return attaquer;
}

bool Unite::attaquer(Case* c) {
    return attaquer(c,m_AttaqueParDefaut);
}

void Unite::attaquer(Entite* e) {
    unsigned int i =0;
    bool Attaquer = false;
    while(i<e->getPosition().size() && !Attaquer)
    {
       Attaquer = this->attaquer(e->getPosition()[i]);
       i++;
    }
}

void Unite::attaquer(Entite* e, AttaqueDeBase* a) {
    unsigned int i =0;
    bool Attaquer = false;
    while(i<e->getPosition().size() && !Attaquer)
    {
    Attaquer = this->attaquer(e->getPosition()[i],a);
    i++;
    }
}

void Unite::attaquer(Entite* e, Sort* a) {
    unsigned int i =0;
    bool Attaquer = false;
    while(i<e->getPosition().size() && !Attaquer)
    {
    Attaquer = this->attaquer(e->getPosition()[i],a);
    i++;
    }
}

int Unite::getMouvement() {
    return m_mouvement + getJoueur()->getListeBonusJoueur()[5] + v_bonus[3];
}

Unite::~Unite() {

}

void Unite::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Entite::mouseReleaseEvent(event);
    if(((Case*)parentItem())->parent()->getFlag()==attente)
        ((Case*)parentItem())->parent()->setBoutons(unite, getJoueur()->getNumero());
    else
        ((Case*)parentItem())->parent()->setFlag(attente);
}

Sort* Unite::getSort(int sort) {
    map <string,Sort*>::iterator it = v_sort.begin();
    for(int i = 0; i < sort; i++)
        it++;
    return it->second;
}

void Unite::appliquerEffet() {
    vector<Effet*>::iterator it = v_effet.begin();
    for(int i = 0; i < v_effet.size() ;i++) {
        v_effet[i]->appliquerEffetUnite(getPosition()[0]);
        if(v_effet[i]->decreaseTour())
            enleverEffet(it);
        it++;
    }
    getPosition()[0]->declencherEffets();
}
