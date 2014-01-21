#include "Plateau.h"
#include "Batiment.h"
#include "Tour.h"
#include "Chateau.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QStyle>
#include <sstream>
#include <string>
#include <typeinfo>


#define SIZE 36


Plateau::Plateau(string nomPlateau) : QGraphicsScene() {
    selected=NULL;
    flag=attente;
    nom = NULL;
    mvt = NULL;
    atk = NULL;
    vie = NULL;
    Batiment* bat1;
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
            int size,x,y,joueur;
            catBatiments type;
            fichierPlateau.read((char*)&joueur, sizeof(int));
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
                            bat1 = new Chateau(plateau[x+j][y+i],cases,NULL,"Chateau");
                            v_Batiment.push_back(bat1);
                            break;
                        }
                        case tour : {
                            Batiment* bat = new Tour(plateau[x+j][y+i],cases[0],NULL,"Tour");
                            v_Batiment.push_back(bat);
                            break;
                        }
                        default :
                            break;
                    }
                }
            }
        }



    att = new QPushButton("Attaquer");
    att->setToolTip("Permet d'utiliser l'attaque de base de l'unite selectionne.");
    att->setGeometry(10,SIZE*(m_hauteur+1),80,25);
    addWidget(att);
    connect(att,SIGNAL(released()),this, SLOT(handleAtt()));

    sorts = new QPushButton("Sorts");
    sorts->setToolTip("Permet de lancer les sorts de l'unité");
    sorts->setGeometry(110,SIZE*(m_hauteur+1),80,25);
    addWidget(sorts);

    dep = new QPushButton("Deplacer");
    dep->setToolTip("Permet de deplacer l'unite selectionne.");
    dep->setGeometry(210,SIZE*(m_hauteur+1),80,25);
    addWidget(dep);
    connect(dep, SIGNAL(released()), this, SLOT(handleDep()));

    capt = new QPushButton("Capturer");
    capt->setToolTip("Permet de capturer le batiment à cote de l'unite selectionne.");
    capt->setGeometry(310,SIZE*(m_hauteur+1),80,25);
    addWidget(capt);

    annuler = new QPushButton("Annuler");
    annuler->setToolTip("Permet d'utiliser l'attaque de base de l'unite selectionne.");
    annuler->setGeometry(410,SIZE*(m_hauteur+1),80,25);
    addWidget(annuler);

    fint = new QPushButton("Fin de tour");
    fint->setToolTip("Permet d'utiliser l'attaque de base de l'unite selectionne.");
    fint->setGeometry(510,SIZE*(m_hauteur+1),90,25);
    addWidget(fint);

    jserveur = new Joueur(1,1);
    jclient = new Joueur(1,0);

    bat1->setJoueur(jclient);

    pop = new QProgressBar;
    pop->setGeometry(550, 10, 80, 25);
    pop->setMaximum(jclient->getPopulationMax());
    pop->setAlignment(Qt::AlignCenter);

    PtAction = new QProgressBar;
    PtAction->setGeometry(550, 40, 80, 25);
    PtAction->setMaximum(jclient->getPtActionMax());
    PtAction->setAlignment(Qt::AlignCenter);

    addWidget(pop);

    addWidget(PtAction);

    update();

    eteindreButtons();

    //--------------------------------
    //--------------------------------

    Unite* ch=new Chevalier(plateau[8][8],plateau[8][8],jclient);
    Unite* vol=new Voleur(plateau[7][8],plateau[7][8],jclient);
    Unite* pret=new Pretre(plateau[6][8],plateau[6][8],jclient);
    Unite* mage=new Magicien(plateau[5][8],plateau[5][8],jclient);
    Unite* guer=new Guerrier(plateau[4][8],plateau[4][8],jclient);


    Unite* ch2=new Chevalier(plateau[8][7],plateau[8][7],jserveur);
    Unite* vol2=new Voleur(plateau[7][7],plateau[7][7],jserveur);
    Unite* pret2=new Pretre(plateau[6][7],plateau[6][7],jserveur);
    Unite* mage2=new Magicien(plateau[5][7],plateau[5][7],jserveur);
    Unite* guer2=new Guerrier(plateau[4][7],plateau[4][7],jserveur);


    Batiment* t=new Tour(plateau[1][1],plateau[1][1],NULL,"Tour");
    vector<Case*> ensCase;
    ensCase.push_back(plateau[2][2]);
    ensCase.push_back(plateau[2][3]);
    ensCase.push_back(plateau[3][2]);
    ensCase.push_back(plateau[3][3]);
    Batiment* c=new Chateau(plateau[1][1],ensCase,jclient,"Chateau");

    //-----------------------------
    //-----------------------------

}

bool Plateau::isFini(ifstream& fichier) {
    bool aLaFin = fichier.peek()==EOF;
    if (fichier.eof())
        fichier.clear();
    return aLaFin;
}

void Plateau::handleDep() {
    highlight(((Unite*)selected)->getPosition()[0],((Unite*)selected)->getMouvement()+((Unite*)selected)->getJoueur()->getListeBonusJoueur()[mouvement]);
    setFlag(deplacement);
}

void Plateau::setSelect(QGraphicsItem *c){
    if (selected)
        selected->setSelected(false);
    selected=c;
    selected->setSelected(true);
}

Plateau::~Plateau() {
    for ( int i=0; i < m_largeur; i++)
        delete [] plateau[i]; 
    delete [] plateau;
}

void Plateau::update()
{
pop->setValue(jclient->getPopulation());
pop->setFormat("%v/%m");

PtAction->setValue(jclient->getPtAction());
PtAction->setFormat("%v/%m");
}


void Plateau::afficheInfoUnite(Entite *u)
{
    nom = new QLabel("Nom : " + *new QString(u->Getnom().c_str()));
    nom->setGeometry(550, 70, 105, 25);
    addWidget(nom);
    vie = new QLabel("Point de Vie : " + QString::number(u->getVie()));
    vie->setGeometry(550, 100, 105, 25);
    addWidget(vie);
    if(typeid(*u) == typeid(Chevalier)  ||
       typeid(*u) == typeid(Pretre)     ||
       typeid(*u) == typeid(Magicien)   ||
       typeid(*u) == typeid(Guerrier)   ||
       typeid(*u) == typeid(Voleur)     ||
       typeid(*u) == typeid(Archer))
    {
    mvt = new QLabel("Mouvement : " + QString::number(((Unite*)u)->getMouvement()));
    mvt->setGeometry(550, 130, 105, 25);
    addWidget(mvt);
    atk = new QLabel("Attaque : " + QString::number(((Unite*)u)->getMouvement()));
    atk->setGeometry(550, 160, 105, 25);
    addWidget(atk);
    }
}

void Plateau::cacheInfoUnite()
{
    delete nom;
    delete vie;
    delete mvt;
    delete atk;
}

void Plateau::InfoNull()
{
    nom = NULL;
    mvt = NULL;
    atk = NULL;
    vie = NULL;
}

void Plateau::handleAtt(){
    QList<QGraphicsItem *> selection = selectedItems();
    if (selection.size()>0)
        setSelect(selection[0]);
    setFlag(attaque);
}

void Plateau::allumerButtons(){
att->setEnabled(true);
dep->setEnabled(true);
sorts->setEnabled(true);
}

void Plateau::eteindreButtons(){
    att->setEnabled(false);
    dep->setEnabled(false);
    sorts->setEnabled(false);
}

void Plateau::intInvocGue()
{
  setUnitInvoc(1);
  setFlag(invoquer);
}
void Plateau::intInvocArc()
{
  setUnitInvoc(2);
  setFlag(invoquer);
}
void Plateau::intInvocChe()
{
  setUnitInvoc(3);
  setFlag(invoquer);
}
void Plateau::intInvocMag()
{
  setUnitInvoc(4);
  setFlag(invoquer);
}
void Plateau::intInvocPre()
{
  setUnitInvoc(5);
  setFlag(invoquer);
}
void Plateau::intInvocVol()
{
  setUnitInvoc(6);
  setFlag(invoquer);
}

void Plateau::uniteInvocable()
{
    guer = new QPushButton;
    guer->setToolTip("guerrier");
    guer->setIcon(QIcon("images/Guerrier1.png"));
    guer->setGeometry(550,190,50,50);
    addWidget(guer);
    connect(guer, SIGNAL(released()), this, SLOT(intInvocGue()));

    arch = new QPushButton;
    arch->setToolTip("archer");
    arch->setIcon(QIcon("images/Archer1.png"));
    arch->setGeometry(600,190,50,50);
    addWidget(arch);
    connect(arch, SIGNAL(released()), this, SLOT(intInvocArc()));

    chev = new QPushButton;
    chev->setToolTip("chevalier");
    chev->setIcon(QIcon("images/Chevalier1.png"));
    chev->setGeometry(550,240,50,50);
    addWidget(chev);
    connect(chev, SIGNAL(released()), this, SLOT(intInvocChe()));

    mag = new QPushButton;
    mag->setToolTip("magicien");
    mag->setIcon(QIcon("images/Magicien1.png"));
    mag->setGeometry(600,240,50,50);
    addWidget(mag);
    connect(mag, SIGNAL(released()), this, SLOT(intInvocMag()));

    pret = new QPushButton;
    pret->setToolTip("pretre");
    pret->setIcon(QIcon("images/Pretre1.png"));
    pret->setGeometry(550,290,50,50);
    addWidget(pret);
    connect(pret, SIGNAL(released()), this, SLOT(intInvocPre()));

    vol = new QPushButton;
    vol->setToolTip("voleur");
    vol->setIcon(QIcon("images/Voleur1.png"));
    vol->setGeometry(600,290,50,50);
    addWidget(vol);
    connect(vol, SIGNAL(released()), this, SLOT(intInvocVol()));
}

void Plateau::deleteUniteInvocable()
{
    delete arch;
    delete guer;
    delete chev;
    delete vol;
    delete mag;
    delete pret;
}

void Plateau::highlight(Case* c, int portee) {
    QColor color = Qt::red;
    if (portee==0) {
        color=Qt::white;
        portee=m_largeur*m_hauteur;
        c->setBrush(*new QBrush(color));
    }

    for (int i=0; i<=portee; i++) {
        for (int j=0; j<=portee-i; j++) {
            if (i+c->getX()<m_largeur&&j+c->getY()<m_hauteur) {
                if (color==Qt::white||porteePossible(c, plateau[i+c->getX()][j+c->getY()])) {
                    plateau[i+c->getX()][j+c->getY()]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()-i>=0&&c->getY()-j>=0) {
                if (color==Qt::white||porteePossible(c, plateau[c->getX()-i][c->getY()-j])) {
                    plateau[c->getX()-i][c->getY()-j]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()+i<m_largeur&&c->getY()-j>=0) {
                if (color==Qt::white||porteePossible(c, plateau[c->getX()+i][c->getY()-j])) {
                    plateau[c->getX()+i][c->getY()-j]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()-i>=0&&c->getY()+j<m_hauteur) {
                if (color==Qt::white||porteePossible(c, plateau[c->getX()-i][c->getY()+j])) {
                    plateau[c->getX()-i][c->getY()+j]->setBrush(*new QBrush(color));
                }
            }
        }
    }
}

bool Plateau::porteePossible(Case *c1, Case *c2) {
    vector<Case*> occupees;
    vector<Case*> libres;
    cout<<"c2.x = "<<c2->getX()<<", ";
    cout<<"c2.y = "<<c2->getY()<<endl;
    int minX = (c1->getX()<c2->getX()?c1->getX():c2->getX());//7
    int maxX = (c1->getX()>c2->getX()?c1->getX():c2->getX());//8
    int minY = (c1->getY()<c2->getY()?c1->getY():c2->getY());//8
    int maxY = (c1->getY()>c2->getY()?c1->getY():c2->getY());//8
    for (int i=minX; i<maxX; i++) {
        for (int j=minY; j<maxY; j++) {
            if (plateau[i][j]->isOccupee()&&(i!=minX||j!=minY)) {
                occupees.push_back(plateau[i][j]);
                    cout<<"obstacle x = "<<i<<", "<<flush;
                    cout<<"obstacle y = "<<j<<endl<<flush;
            }
            else
                libres.push_back(plateau[i][j]);
        }
    }

    bool possible=(occupees.size()==0);
    for (unsigned int i=0; i<occupees.size()&&!possible; i++) {
        if (occupees[i]->getX()>c2->getX()) {
            if (occupees[i]->getY()>c2->getY()) {
                if (((occupees[i]->getY()-c2->getY())-(occupees[i]->getX()-c2->getX())>0))
                    possible=true;
            }
            else
                if (((occupees[i]->getY()-c2->getY())+(occupees[i]->getX()-c2->getX())<0))
                    possible=true;
                else {
                    cout<<"x = "<<c2->getX()<<", "<<flush;
                    cout<<"y = "<<c2->getY()<<endl<<flush;
                }
        }
        if (occupees[i]->getX()<c2->getX()) {
            if (occupees[i]->getY()>c2->getY()) {
                if (((occupees[i]->getY()-c2->getY())+(occupees[i]->getX()-c2->getX())>0))
                    possible=true;
            }
            else
                if (((occupees[i]->getY()-c2->getY())-(occupees[i]->getX()-c2->getX())<0))
                    possible=true;
        }
    }

    cout<<"-----------------"<<endl;

    return possible;
}
