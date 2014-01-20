#include "Plateau.h"
#include "Batiment.h"
#include "Tour.h"
#include "Chateau.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#define SIZE 36


Plateau::Plateau(string nomPlateau) : QGraphicsScene() {
    selected=NULL;
    flag=attente;

    ifstream fichierPlateau(nomPlateau.c_str(), ios::in | ios::binary);
    if (fichierPlateau.fail()) { // Si echec de l'ouverture
            cout << "Impossible d'ouvrir ou de créer le fichier" << endl;
            exit(0);
    }
    fichierPlateau.seekg(0,ios_base::beg);

    fichierPlateau.read((char*)&m_largeur ,sizeof(int));
    fichierPlateau.read((char*)&m_hauteur,sizeof(int));
    //-----initialisation du plateau (tableau de Case* à 2 dimensions)
    plateau = new Case**[m_largeur];
    for (int i=0; i< m_largeur; i++) {
        plateau[i] = new Case*[m_hauteur];
        for (int j=0; j<m_hauteur; j++) {
            plateau[i][j] = new Case(i,j,this);
            this->addItem(plateau[i][j]);
        }
    }

    while(!isFini(fichierPlateau)) {
        int size,x,y;
        catBatiments type;
        fichierPlateau.read((char*)&type, sizeof(catBatiments));
        fichierPlateau.read((char*)&size, sizeof(int));
        fichierPlateau.read((char*)&x, sizeof(int));
        fichierPlateau.read((char*)&y, sizeof(int));

        vector<Case*> cases;
        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                cases.push_back(plateau[x+j][y+i]);
            }
        }

        for (int i=0; i<size; i++) {
            for (int j=0; j<size; j++) {
                switch (type) {
                    case chateau : {
                        Batiment* bat = new Chateau(plateau[x+j][y+i],cases,NULL,"Chateau");
                        break;
                    }
                    case tour : {
                        Batiment* bat = new Tour(plateau[x+j][y+i],cases,NULL,"Tour");
                        break;
                    }
                    default :
                        break;
                }
            }
        }
    }


    QPushButton* dep = new QPushButton("Déplacer");
    dep->setGeometry(10,SIZE*(m_hauteur+1),80,25);
    addWidget(dep);
    connect(dep, SIGNAL(released()), this, SLOT(handleDep()));

    Joueur* j = new Joueur(1,1);

    vector<Case*> cases;
    cases.push_back(plateau[8][8]);
    Unite* ch=new Chevalier(plateau[8][8],cases,j);
    //ch->deplacer(plateau[8][7]);

    pop = new QProgressBar;
    pop->setGeometry(550, 10, 80, 25);
    PtAction = new QProgressBar;
    PtAction->setGeometry(550, 40, 80, 25);

    pop->setValue(j->getPopulation());
    addWidget(pop);
    PtAction->setValue(j->getPtAction());
    addWidget(PtAction);
}

bool Plateau::isFini(ifstream& fichier) {
    bool aLaFin = fichier.peek()==EOF;
    if (fichier.eof())
        fichier.clear();
    return aLaFin;
}

void Plateau::handleDep() {
    QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size()>0)
        setSelected(selection[0]);
    setFlag(deplacement);
}

Plateau::~Plateau() {
    for ( int i=0; i < m_largeur; i++)
        delete [] plateau[i]; 
    delete [] plateau;
}
