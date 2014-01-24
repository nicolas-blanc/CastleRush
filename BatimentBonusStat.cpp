#include "BatimentBonusStat.h"
#include "Plateau.h"
#include "QMessageBox"

BatimentBonusStat::BatimentBonusStat(QGraphicsItem* parent, vector<Case*>& ensCase, string nom, int stat)
: Batiment(parent, ensCase, nom, -1, -1) {
    setStat(stat);
    setBonus(0);
    setNbTours(0);
    if(nom == "Tour de Magie") {
        this->setPixmap(* new QPixmap("images/ChateauCentral.png"));
    } else if (nom == "Campement") {
        this->setPixmap(* new QPixmap("images/Campement.png"));
    } else {
        this->setPixmap(* new QPixmap("images/Village.png"));
    }
}

void BatimentBonusStat::modifBonus() {
// Modifie le bonus dans le vector de joueur, en fonction du bonus et du nombre de tours
    if(getNbTours()<14)
    {
    setNbTours(getNbTours()+1);

    switch(getStat()) {
        case 0:
            setBonus(getBonus() + getNbTours()/4);
            break;
        case 1:
            setBonus(getBonus() + getNbTours()/4);
            break;
        case 2:
            setBonus(getBonus() + getNbTours()/8);
            break;
        case 3:
            setBonus(getBonus() + getNbTours()/6);
            break;
        case 4:
            setBonus(getBonus() + getNbTours()/6);
            break;
        default:
            // appel d'exception
            break;
        }
    miseAJourBonus();
    }
}

void BatimentBonusStat::Bonus() {
    switch(getStat()) {
        case 0:
            setBonus(5);
            break;
        case 1:
            setBonus(1/*nbToursTotal/2*/);//nbToursTotal variable global
            break;
        case 2:
            setBonus(1);
            break;
        case 3:
            setBonus(1);
            break;
        case 4:
            setBonus(2);
            break;
        default:
            // appel exception
            break;
    }
    miseAJourBonus();
}

void BatimentBonusStat::randomStat() {
    setStat(rand_a_b(2,5));
}

void BatimentBonusStat::changementProprio(Joueur *j) {
    if(this->getJoueur() != NULL)
    {
    this->getJoueur()->setListeBonusJoueur(getStat(), 0);
    Entite::setJoueur(j);
    }
    else
    {
       Entite::setJoueur(j);
    }

    getJoueur()->setBatiment(this);
    if(getStat()>1)
        randomStat();

    Bonus();
    setNbTours(0);
}

void BatimentBonusStat::miseAJourBonus()
{
    this->getJoueur()->setListeBonusJoueur(getStat(), getBonus());
}

void BatimentBonusStat::mouseReleaseEvent(QGraphicsSceneMouseEvent *)
{

    if(((Case*)parentItem())->parent()->getFlag()==capture)
    {
        if((((Unite*)((Case*)parentItem())->parent()->getSelect())->getJoueur()->getPtActionMax()/2) <= ((Unite*)((Case*)parentItem())->parent()->getSelect())->getJoueur()->getPtAction())
        {

            ((Unite*)((Case*)parentItem())->parent()->getSelect())->getJoueur()->modifPtAction(((Unite*)((Case*)parentItem())->parent()->getSelect())->getJoueur()->getPtActionMax()/2);
            ((Case*)parentItem())->parent()->setInvocateur(((Unite*)((Case*)parentItem())->parent()->getSelect()));
            ((Case*)parentItem())->parent()->setBatimentBonus(this);
            ((Case*)parentItem())->parent()->updatePopPt();
            ((Unite*)((Case*)parentItem())->parent()->getSelect())->setActif(false);
            ((Case*)parentItem())->parent()->setFlag(attente);
        }
        else
        {
            QMessageBox popup;
            popup.setText("Vous n'avez pas assez de point d'action");
            popup.exec();
        }
    }
    ((Case*)parentItem())->parent()->setBoutons(batiment);
    ((Case*)parentItem())->parent()->afficheInfoUnite(this);
}


