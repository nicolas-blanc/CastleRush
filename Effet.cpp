#include "Effet.h"
#include "Case.h"
#include "Joueur.h"
#include <QMessageBox>
#include "Plateau.h"

Effet::Effet(Joueur *joueur, int tour) {
    m_nbTour = tour;
    m_joueur = joueur;
}

bool Effet::decreaseTour() {
    m_nbTour--;
    if(m_nbTour == 0)
        return true;
    else
        return false;
}

void Effet::appliquerEffetCase(Case * c) {
    c->ajouterEffet(this);
}

DegenVie::DegenVie(Joueur * joueur, int nbTour, int malus) : Effet(joueur,nbTour) { m_malus = malus; }

void DegenVie::appliquerEffetUnite(Case *c) {
    c->getUnite()->modifierVie(m_malus);

    if (!c->contientBatiment()&&c->isOccupee() &&c->getOccupant()->getVie()==0){
        QPixmap *tombe;
        tombe=new QPixmap("images/Coffin.png");
        (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));

        c->getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
        c->setOccupant(NULL);
    }
    else if(c->isOccupee() && c->getOccupant()->Getnom()== "Chateau" && c->getOccupant()->getVie()==0)
    {
        QPixmap *tombe;
        tombe=new QPixmap("images/ChateauDetruit.png");
        (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));

        QMessageBox popup;
        popup.setText("Victoire " + c->getOccupant()->getJoueur()->getPseudo() + "!");
        popup.exec();

         c->parent()->finDuJeu();

    }
    else if(c->isOccupee() && c->getOccupant()->Getnom() == "Tour" && c->getOccupant()->getVie()==0)
    {
        QPixmap *tombe;
        tombe=new QPixmap("images/TourDetruite.png");
        (c->getOccupant())->setPixmap(tombe->copy(0,96,32,32));

        c->parent()->supprimerTour((Batiment*)c->getOccupant());
        c->getOccupant()->setFlag(QGraphicsItem::ItemIsSelectable,false);
        c->setOccupant(NULL);
    }
}

MalusMouvement::MalusMouvement(Joueur *joueur, int nbTour, int malus) : Effet(joueur,nbTour) { m_malus = malus; }

void MalusMouvement::appliquerEffetUnite(Case *c) {
    if(c->getUnite())
    ((Unite*) c->getUnite())->modifBonus(3,-m_malus);
}

void MalusMouvement::enleverEffetUnite(Case *c)
{
    if(c->getUnite())
        ((Unite*) c->getUnite())->modifBonus(3,0);
}

BonusDegat::BonusDegat(Joueur * joueur,int nbTour, int bonus) : Effet(joueur,nbTour) { m_bonus = bonus;}

void BonusDegat::appliquerEffetUnite(Case *c) {
    ((Unite*) c->getUnite())->modifBonus(1,m_bonus);
}

void BonusDegat::enleverEffetUnite(Case *c)
{
    if(c->getUnite())
        ((Unite*) c->getUnite())->modifBonus(1,0);
}
