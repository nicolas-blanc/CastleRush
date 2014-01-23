#include "Sort.h"
#include "Plateau.h"
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QSequentialAnimationGroup>
#define SIZE 36

Sort::Sort(string nom, int degat, int portee, int ptAction, Entite* ent) : Attaque(portee,degat,ptAction,ent) {
    m_nomSort = nom;
}

void Sort::lancerAttaque(Case *) {}

AttaquePuissante::AttaquePuissante(string nom, int degat, int portee, int ptAction, Entite* ent) : Sort(nom,degat,portee,ptAction,ent) {
    QPixmap* atq = new QPixmap("images/Attack2-2.png");
    for (int i=0; i<5; i++)
        this->setImageAttaque(new QPixmap(atq->copy(50*i,0,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(0,50,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(50,50,50,50)));
    this->setImageAttaque(new QPixmap(atq->copy(100,50,50,50)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void AttaquePuissante::lancerAttaque(Case *c)
{
    animationAttaque(m_Entite->getPosition()[0],c);
    c->transmettreAttaque(this->getDegat());
}

void AttaquePuissante::animationAttaque(Case *c1, Case *c2) {
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

    for (int k=0; k<2; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(20);
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

Charge::Charge(string nom, int degat, int portee, int ptAction, Entite* ent) : Sort(nom,degat,portee,ptAction,ent) {
    QPixmap* atq = new QPixmap("images/Sword5-2.png");
    for (int j=0;j<5;j++)
        for (int i=0; i<5; i++)
            this->setImageAttaque(new QPixmap(atq->copy(50*i,j*50,50,50)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void Charge::lancerAttaque(Case *c) {
    int x = c->getX() - m_Entite->getPosition()[0]->getX();
    int y = c->getY() - m_Entite->getPosition()[0]->getY();

    c->transmettreAttaque(this->getDegat());
    animationAttaque(m_Entite->getPosition()[0],c);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()+x,c->getY()+y)->transmettreAttaque(this->getDegat()-1);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()+(2*x),c->getY()+(2*y))->transmettreAttaque(this->getDegat()-1);
}

void Charge::animationAttaque(Case *c1, Case *c2) {
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

    //for (int k=0; k<2; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(20);
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

AttaqueEmpoisonnee::AttaqueEmpoisonnee(string nom, int degat, int portee, int ptAction, Entite* ent) : Sort(nom,degat,portee,ptAction,ent) {
    m_effet = new DegenVie(ent->getJoueur(),2,1);
}

void AttaqueEmpoisonnee::lancerAttaque(Case *c) {
    animationAttaque(m_Entite->getPosition()[0],c);
    if (c->isOccupee()) {
        c->transmettreAttaque(this->getDegat());
        ((Unite*) c->getUnite())->ajouterEffet(m_effet);
    }
}

void AttaqueEmpoisonnee::animationAttaque(Case *c1, Case *c2) {

}

GlypheGel::GlypheGel(string nom, int portee, int ptAction, Entite* ent) : Sort(nom,0,portee,ptAction,ent) {
    m_effet = new MalusMouvement(ent->getJoueur(),3,2);
    QPixmap* atq = new QPixmap("images/Ice2-1.png");
    for (int j=0; j<3; j++)
        for (int i=0; i<5; i++)
            this->setImageAttaque(new QPixmap(atq->copy(60*i,j*60,60,60)));
    this->setImageAttaque(new QPixmap(atq->copy(0,180,60,60)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void GlypheGel::lancerAttaque(Case *c) {
    animationAttaque(m_Entite->getPosition()[0],c);
    c->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()-1,c->getY())->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX()+1,c->getY())->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX(),c->getY()-1)->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->getCase(c->getX(),c->getY()+1)->ajouterEffet(m_effet);
    m_Entite->getJoueur()->getPlateau()->highlight(c,1,Qt::blue);
}

void GlypheGel::animationAttaque(Case *c1, Case *c2) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
    float decalageX = (c2->getX()-c1->getX())*SIZE;
    float decalageY = (c2->getY()-c1->getY())*SIZE;

    QPropertyAnimation *setoff = new QPropertyAnimation(this, "offsetAtk");
    setoff->setDuration(1);
    setoff->setStartValue(QPointF(c2->getX()*SIZE-5,c2->getY()*SIZE-5));
    setoff->setEndValue(QPointF(c2->getX()*SIZE-5,c2->getY()*SIZE-5));
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

    for (int k=0; k<2; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(50);
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

Soin::Soin(string nom, int degat, int portee, int ptAction, Entite* ent) : Sort(nom,degat,portee,ptAction,ent) {
    QPixmap* atq = new QPixmap("images/Heal1-2.png");
    for (int j=0; j<6; j++)
        for (int i=0; i<5; i++)
            this->setImageAttaque(new QPixmap(atq->copy(50*i,j*50,50,50)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void Soin::lancerAttaque(Case *c) {
    animationAttaque(m_Entite->getPosition()[0],c);
    c->transmettreAttaque(this->getDegat());
}

void Soin::animationAttaque(Case *c1, Case *c2) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
    float decalageX = (c2->getX()-c1->getX())*SIZE;
    float decalageY = (c2->getY()-c1->getY())*SIZE;

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

    //for (int k=0; k<5; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(50);
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

Concentration::Concentration(string nom, int degat, int portee, int ptAction, Entite* ent) : Sort(nom,degat,portee,ptAction,ent) {
    m_effet = new BonusDegat(ent->getJoueur(),2,1);
    QPixmap* atq = new QPixmap("images/Concentration1-2.png");
    for (int j=0; j<3; j++)
        for (int i=0; i<5; i++)
            this->setImageAttaque(new QPixmap(atq->copy(60*i,j*60,60,60)));
    this->setImageAttaque(new QPixmap(atq->copy(0,180,60,60)));
    ((Case*)m_Entite->parentItem())->parent()->addItem(&atk);
}

void Concentration::lancerAttaque(Case *c) {
    animationAttaque(m_Entite->getPosition()[0],c);
    ((Unite*) c->getUnite())->ajouterEffet(m_effet);
}

void Concentration::animationAttaque(Case *c1, Case *c2) {
    QSequentialAnimationGroup *group = new QSequentialAnimationGroup();
    float decalageX = (c2->getX()-c1->getX())*SIZE;
    float decalageY = (c2->getY()-c1->getY())*SIZE;

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

    for (int k=0; k<2; k++)
        for (unsigned int i=0; i<getImageAttaque().size(); i++) {
            QPropertyAnimation *animPix = new QPropertyAnimation(this, "pixmap");
            animPix->setDuration(50);
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
