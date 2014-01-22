#include "Tour.h"
#include <math.h>
#include "Case.h"
#include "Plateau.h"

Tour::Tour(QGraphicsItem* parent, Case* c, Joueur* j, string nom)
: Batiment(parent, c, j, nom, 0, 10),m_attaque(5)
{
    setPixmap(* new QPixmap("images/Tour1"));
}

Tour::Tour(QGraphicsItem* parent, Case* c, string nom)
: Batiment(parent, c, nom, 0, 10),m_attaque(5)
{
    setPixmap(* new QPixmap("images/Tour1"));
}

void Tour::attaquer(Case* c) {
    getAttaque().lancerAttaque(c);
}


void Tour::attaqueAuto()
{
    Entite* danger_entite;
    float distance;
    float distance_danger;
    vector<Entite*> entite_presentent;
    vector<Case*> ma_position = getPosition();
    for(int x =0; x<(ma_position[0]->getX()+m_attaque.getPortee()); x++)
    {
        for(int y = 0; y<ma_position[0]->getY()+m_attaque.getPortee(); y++)
        {
            Case *caseoccupee = new Case(x,y,((Case*)parentItem())->parent());
            if(caseoccupee->isOccupee())
            {
                entite_presentent.push_back(ma_position[0]->getOccupant());
            }
        }
    }

    distance_danger = sqrt(((getJoueur()->getBatiment("Chateau")->getPosition()[0]->getX()
                -entite_presentent[0]->getPosition()[0]->getX())^2)+
                ((getJoueur()->getBatiment("Chateau")->getPosition()[0]->getY()
                -entite_presentent[0]->getPosition()[0]->getY())^2));
    danger_entite = entite_presentent[0];
    for(unsigned int i =1; i<entite_presentent.size(); i++)
    {
        cout << "test " << endl << flush;
        distance = sqrt(((getJoueur()->getBatiment("Chateau")->getPosition()[0]->getX()
                -entite_presentent[i]->getPosition()[0]->getX())^2)+
                ((getJoueur()->getBatiment("Chateau")->getPosition()[0]->getY()
                -entite_presentent[i]->getPosition()[0]->getY())^2));
        if(distance<distance_danger)
        {
            distance_danger = distance;
            danger_entite = entite_presentent[0];
        }
    }

    attaquer(danger_entite->getPosition()[0]);
}

void Tour::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    Batiment::mouseReleaseEvent(event);
    ((Case*)parentItem())->parent()->setBoutons(batTour);
    cout <<"kbvhjvjhvjvjvjvv :::  " << this->getJoueur()->getNumero() << endl << flush;
}
