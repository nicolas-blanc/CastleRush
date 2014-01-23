#include "AttaqueDeBase.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#include "Plateau.h"
#define SIZE 36

AttaqueDeBase::AttaqueDeBase(int portee, Entite* ent)
: Attaque(portee,1,1,ent) {
    QPixmap* atq = new QPixmap("images/Attack5-2.png");
    for (int i=0; i<5; i++)
        this->setImageAttaque(new QPixmap(atq->copy(50*i,0,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(0,50,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(50,50,50,50)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

AttaqueDeBase::AttaqueDeBase(int portee, int deg, Entite* ent)
: Attaque(portee,deg,1,ent) {
    QPixmap* atq = new QPixmap("images/Attack5-2.png");
    for (int i=0; i<5; i++)
        this->setImageAttaque(new QPixmap(atq->copy(50*i,0,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(0,50,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(50,50,50,50)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void AttaqueDeBase::lancerAttaque(Case* c) {
    animationAttaque(m_Entite->getPosition()[0],c);
    c->transmettreAttaque(this->getDegat()+c->getUnite()->getJoueur()->getListeBonusJoueur()[2]);
}

void AttaqueDeBase::animationAttaque(Case* c1, Case* c2) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
    float decalageX = (c2->getX()-c1->getX())*SIZE/2;
    float decalageY = (c2->getY()-c1->getY())*SIZE/2;

    QPropertyAnimation *setoff = new QPropertyAnimation(this, "offsetAtk");
    setoff->setDuration(1);
    setoff->setStartValue(QPointF(m_Entite->offset().x()+decalageX,m_Entite->offset().y()+decalageY));
    setoff->setEndValue(QPointF(m_Entite->offset().x()+decalageX,m_Entite->offset().y()+decalageY));
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

    for (int k=0; k<3; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(30);
            animPix->setStartValue(i);
            animPix->setEndValue(i);
            group->addAnimation(animPix);
        }
    QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
    animPix->setDuration(1);
    animPix->setStartValue(-1);
    animPix->setEndValue(-1);
    group->addAnimation(animPix);

    group->start();
}
