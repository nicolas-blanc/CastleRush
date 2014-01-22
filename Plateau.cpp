#include "Plateau.h"
#include "Batiment.h"
#include "Tour.h"
#include "Chateau.h"
#include "BatimentBonusStat.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <QGraphicsSceneMouseEvent>
#include <QPushButton>
#include <QStyle>
#include <sstream>
#include <QString>
#include <typeinfo>
#include <QMessageBox>


#define SIZE 36


Plateau::Plateau(vector<Joueur*> joueurs, string nomPlateau) : QGraphicsScene() {
    this->setNombreTour(1);
    this->setNombreTourJoueur(1);
    selected=NULL;
    flag=attente;
    nom = NULL;
    mvt = NULL;
    atk = NULL;
    vie = NULL;
    arch = NULL;
    guer = NULL;
    chev = NULL;
    vol = NULL;
    mag = NULL;
    pret = NULL;

    jclient = joueurs[0];
    jserveur = joueurs[1];

    Batiment* bat;
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

        int jTaille = joueurs.size();

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
                        if (!(i-1)&&!(j-1)) {
                            if(joueur < jTaille && joueur != -1) {
                                bat = new Chateau(plateau[x+i][y+j],cases,joueurs[joueur],"Chateau");
                            }
                            else {
                                bat = new Chateau(plateau[x+i][y+j],cases,"Chateau");
                            }
                        }
                            break;
                        }
                        case tour : {
                            if(joueur < jTaille && joueur != -1) {
                                bat = new Tour(plateau[x+i][y+j],cases[0],joueurs[joueur],"Tour");
                            }
                            else {
                                bat = new Tour(plateau[x+i][y+j],cases[0],"Tour");
                            }
                            break;
                        }
                        case campement : {
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Campement",-1);
                                    break;
                            }
                        case village : {
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Village",-2);
                            break;
                            }
                        case magie : {
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Tour de Magie",-3);
                            break;
                        }
                        default :
                            break;
                    }
                    v_Batiment.push_back(bat);
                }
            }
        }

    TOUR = new QLabel("Tour ToTal : " + QString::number(NombreTour) + " -- Tour n°" +QString::number(NombreTourJoueur));
    TOUR->setGeometry(SIZE*(m_largeur+1),(-30),180,25);
    addWidget(TOUR);

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
    connect(fint, SIGNAL(released()), this, SLOT(gestionTour()));

    jserveur = new Joueur(1,1);
    jserveur->setPseudo("Joueur2");
    jclient = new Joueur(1,0);
    jclient->setPseudo("Joueur1");

    j.push_back(jclient);

    j.push_back(jserveur);

    jtour = j[0];

    pop = new QProgressBar;
    pop->setGeometry(SIZE*(m_largeur+1), 10, 80, 25);
    PtAction = new QProgressBar;
    PtAction->setGeometry(SIZE*(m_largeur+1), 40, 80, 25);

    addWidget(pop);

    addWidget(PtAction);

    updatePopPt();

    QMessageBox popup;
    popup.setText("Tour Joueur : " + jtour->getPseudo());
    popup.exec();

    guer = new QPushButton;
    guer->setToolTip("guerrier");
    guer->setIcon(QIcon("images/Guerrier1.png"));
    guer->setIconSize(QSize(30,30));
    guer->setGeometry(10,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(guer);
    connect(guer, SIGNAL(released()), this, SLOT(intInvocGue()));

    arch = new QPushButton;
    arch->setToolTip("archer");
    arch->setIcon(QIcon("images/Archer1.png"));
    arch->setIconSize(QSize(30,30));
    arch->setGeometry(70,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(arch);
    connect(arch, SIGNAL(released()), this, SLOT(intInvocArc()));

    chev = new QPushButton;
    chev->setToolTip("chevalier");
    chev->setIcon(QIcon("images/Chevalier1.png"));
    chev->setIconSize(QSize(30,30));
    chev->setGeometry(130,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(chev);
    connect(chev, SIGNAL(released()), this, SLOT(intInvocChe()));

    mag = new QPushButton;
    mag->setToolTip("magicien");
    mag->setIcon(QIcon("images/Magicien1.png"));
    mag->setIconSize(QSize(30,30));
    mag->setGeometry(190,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(mag);
    connect(mag, SIGNAL(released()), this, SLOT(intInvocMag()));

    pret = new QPushButton;
    pret->setToolTip("pretre");
    pret->setIcon(QIcon("images/Pretre1.png"));
    pret->setIconSize(QSize(30,30));
    pret->setGeometry(250,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(pret);
    connect(pret, SIGNAL(released()), this, SLOT(intInvocPre()));

    vol = new QPushButton;
    vol->setToolTip("voleur");
    vol->setIcon(QIcon("images/Voleur1.png"));
    vol->setIconSize(QSize(30,30));
    vol->setGeometry(310,SIZE*(m_hauteur+1)-12,50,50);
    addWidget(vol);
    connect(vol, SIGNAL(released()), this, SLOT(intInvocVol()));

    nom = new QLabel();
    nom->setGeometry(SIZE*(m_largeur+1), 70, 150, 25);
    addWidget(nom);

    vie = new QLabel();
    vie->setGeometry(SIZE*(m_largeur+1), 100, 150, 25);
    addWidget(vie);

    mvt = new QLabel();
    mvt->setGeometry(SIZE*(m_largeur+1), 130, 150, 25);
    addWidget(mvt);

    atk = new QLabel();
    atk->setGeometry(SIZE*(m_largeur+1), 160, 150, 25);
    addWidget(atk);

    setBoutons(carre);

    //--------------------------------
    //--------------------------------

    Unite* vol=new Voleur(plateau[7][8],plateau[7][8],jclient);
    Unite* pret=new Pretre(plateau[6][8],plateau[6][8],jserveur);
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

void Plateau::gestionTour()
{
    this->setNombreTourJoueur(getNombreTour()/2 + 1);
    this->setNombreTour(getNombreTour()+1);
    jtour->setPtAction(jtour->getPtActionMax());
    jtour = j[1-jtour->getNumero()];
    this->updatePopPt();
    TOUR->setText("Tour ToTal : " + QString::number(NombreTour) + " -- Tour n°" +QString::number(NombreTourJoueur));
    QMessageBox popup;
    popup.setText("Tour Joueur : " + jtour->getPseudo());
    popup.exec();
//    for(int i =0; i<v_Batiment.size(); i++)
//    {
//        if(typeid(*(v_Batiment[i]))==typeid(Tour))
//        {
//            ((Tour*)v_Batiment[i])->attaqueAuto();
//        }
//    }
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

void Plateau::updatePopPt()
{
    cout << "   " << jtour->getNumero() << endl << flush;
    cout << "   " << jtour->getPopulation() << endl << flush;
    pop->setMaximum(jtour->getPopulationMax());
    pop->setValue(jtour->getPopulation());
    pop->setFormat("%v/%m");
    pop->setAlignment(Qt::AlignCenter);

    PtAction->setValue(jtour->getPtAction());
    PtAction->setMaximum(jtour->getPtActionMax());
    PtAction->setFormat("%v/%m");
    PtAction->setAlignment(Qt::AlignCenter);
}


void Plateau::afficheInfoUnite(Entite *u)
{
    mvt->hide();
    atk->hide();
    nom->show();
    nom->setText("Nom : " + QString(u->Getnom().c_str()));
    if(typeid(*u) != typeid(BatimentBonusStat) ){
    vie->show();
    vie->setText("Point de Vie : " + QString::number(u->getVie()));}
    if(typeid(*u) == typeid(Chevalier)  ||
       typeid(*u) == typeid(Pretre)     ||
       typeid(*u) == typeid(Magicien)   ||
       typeid(*u) == typeid(Guerrier)   ||
       typeid(*u) == typeid(Voleur)     ||
       typeid(*u) == typeid(Archer))
    {
        mvt->show();
        mvt->setText("Mouvement : " + QString::number(((Unite*)u)->getMouvement()));
        atk->show();
        atk->setText("Attaque : " + QString::number(((Unite*)u)->getAttaqueParDefaut()->getDegat()));
    }
}

void Plateau::handleAtt(){
    highlightAttaque(((Unite*)selected)->getPosition()[0],((Unite*)selected)->getAttaqueParDefaut()->getPortee()+((Unite*)selected)->getJoueur()->getListeBonusJoueur()[portee]);
    setFlag(attaque);
}

void Plateau::setBoutons(typeElement type, int numJoueur) {
    switch (type) {
    case (carre) : {
        att->hide();
        dep->hide();
        sorts->hide();
        nom->hide();
        vie->hide();
        mvt->hide();
        atk->hide();
        guer->hide();
        mag->hide();
        vol->hide();
        pret->hide();
        chev->hide();
        arch->hide();
        capt->hide();
        break;
    }
    case (batiment) : {
        att->hide();
        dep->hide();
        sorts->hide();
        guer->hide();
        mag->hide();
        vol->hide();
        pret->hide();
        chev->hide();
        arch->hide();
        capt->hide();
        vie->hide();
        break;
    }
    case (batTour) : {
        att->hide();
        dep->hide();
        sorts->hide();
        guer->hide();
        mag->hide();
        vol->hide();
        pret->hide();
        chev->hide();
        arch->hide();
        capt->hide();
        vie->show();
        break;
    }
    case (batChateau) : {
        att->hide();
        dep->hide();
        sorts->hide();
        capt->hide();
        vie->show();
        if(numJoueur==this->getJoueurTour()->getNumero())
        {
        guer->show();
        mag->show();
        vol->show();
        pret->show();
        chev->show();
        arch->show();
        }
        break;
    }
    case (unite) : {
        guer->hide();
        mag->hide();
        vol->hide();
        pret->hide();
        chev->hide();
        arch->hide();
        att->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        dep->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        sorts->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        capt->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        setBoutonsUnite(getJoueurTour()->getNumero() == numJoueur);
        break;
    }
    }
}


void Plateau::setBoutonsUnite(bool active) {
    if (active) {
        att->show();
        dep->show();
        sorts->show();
        capt->show();
    }
    else {
        att->hide();
        dep->hide();
        sorts->hide();
        capt->hide();
    }
}

void Plateau::intInvocGue()
{
  setUnitInvoc(guerrier);
  setFlag(invoquer);
}
void Plateau::intInvocArc()
{
  setUnitInvoc(archer);
  setFlag(invoquer);
}
void Plateau::intInvocChe()
{
  setUnitInvoc(chevalier);
  setFlag(invoquer);
}
void Plateau::intInvocMag()
{
  setUnitInvoc(magicien);
  setFlag(invoquer);
}
void Plateau::intInvocPre()
{
  setUnitInvoc(pretre);
  setFlag(invoquer);
}
void Plateau::intInvocVol()
{
  setUnitInvoc(voleur);
  setFlag(invoquer);
}

    void Plateau::highlight(Case* c, int portee) {
        QColor color = Qt::red;
        if (portee==-1) {
            color=Qt::transparent;
            portee=m_largeur*m_hauteur;
            for (int i=0; i<m_largeur; i++)
                for (int j=0; j<m_hauteur; j++)
                    plateau[i][j]->setBrush(*new QBrush(color));
        }
        else {
            vector<Case*> chemin;
            for (int i=0; i<=portee; i++) {
                for (int j=0; j<=portee-i; j++) {
                    if (i+c->getX()<m_largeur&&j+c->getY()<m_hauteur) {
                        chemin=cheminDeplacement(c, plateau[c->getX()+i][c->getY()+j],portee);
                        if (color==Qt::transparent||chemin[chemin.size()-1]!=NULL) {
                            plateau[i+c->getX()][j+c->getY()]->setBrush(*new QBrush(color));
                        }
                    }
                    if (c->getX()-i>=0&&c->getY()-j>=0) {
                        chemin=cheminDeplacement(c, plateau[c->getX()-i][c->getY()-j],portee);
                        if (color==Qt::transparent||chemin[chemin.size()-1]!=NULL) {
                            plateau[c->getX()-i][c->getY()-j]->setBrush(*new QBrush(color));
                        }
                    }
                    if (c->getX()+i<m_largeur&&c->getY()-j>=0) {
                        chemin=cheminDeplacement(c, plateau[c->getX()+i][c->getY()-j],portee);
                        if (color==Qt::transparent||chemin[chemin.size()-1]!=NULL) {
                            plateau[c->getX()+i][c->getY()-j]->setBrush(*new QBrush(color));
                        }
                    }
                    if (c->getX()-i>=0&&c->getY()+j<m_hauteur) {
                        chemin=cheminDeplacement(c, plateau[c->getX()-i][c->getY()+j],portee);
                        if (color==Qt::transparent||chemin[chemin.size()-1]!=NULL) {
                            plateau[c->getX()-i][c->getY()+j]->setBrush(*new QBrush(color));
                        }
                    }
                }
            }
        }
    }

    vector<Case*> Plateau::cheminDeplacement(Case *c1, Case *c2, int portee) {
        if (c1==NULL) {
            vector<Case*> v;
            v.push_back(NULL);
            return v;
        }
        else if ((c1->getX()==c2->getX())&&(c1->getY()==c2->getY())) {
            vector<Case*> v;
            v.push_back(c1);
            return v;
        }
        else if (portee==0) {
            vector<Case*> v;
            v.push_back(NULL);
            return v;
        }

        vector<vector<Case*> > chemins;
        vector<Case*> gauche;
        vector<Case*> droite;
        vector<Case*> avant;
        vector<Case*> arriere;
        droite.push_back(c1);
        gauche.push_back(c1);
        avant.push_back(c1);
        arriere.push_back(c1);
        chemins.push_back(gauche);
        chemins.push_back(droite);
        chemins.push_back(avant);
        chemins.push_back(arriere);

        if (c1->getX()+1<m_largeur&&c1->getX()<=c2->getX()&&!plateau[c1->getX()+1][c1->getY()]->isOccupee()) {
            vector<Case*> res = cheminDeplacement(plateau[c1->getX()+1][c1->getY()],c2,portee-1);
            for (unsigned int i=0; i<res.size(); i++)
                chemins[0].push_back(res[i]);
        }
        else chemins[0].push_back(NULL);
        if (c1->getX()-1>=0&&c1->getX()>=c2->getX()&&!plateau[c1->getX()-1][c1->getY()]->isOccupee()) {
            vector<Case*> res = cheminDeplacement(plateau[c1->getX()-1][c1->getY()],c2,portee-1);
            for (unsigned int i=0; i<res.size(); i++)
                chemins[1].push_back(res[i]);
        }
        else chemins[1].push_back(NULL);
        if (c1->getY()+1<m_hauteur&&c1->getY()<=c2->getY()&&!plateau[c1->getX()][c1->getY()+1]->isOccupee()){
            vector<Case*> res = cheminDeplacement(plateau[c1->getX()][c1->getY()+1],c2,portee-1);
            for (unsigned int i=0; i<res.size(); i++)
                chemins[2].push_back(res[i]);
        }
        else chemins[2].push_back(NULL);
        if (c1->getY()-1>=0&&c1->getY()>=c2->getY()&&!plateau[c1->getX()][c1->getY()-1]->isOccupee()){
            vector<Case*> res = cheminDeplacement(plateau[c1->getX()][c1->getY()-1],c2,portee-1);
            for (unsigned int i=0; i<res.size(); i++)
                chemins[3].push_back(res[i]);
        }
        else chemins[3].push_back(NULL);

        vector<Case*> cheminOK;
        cheminOK.push_back(NULL);

        for (unsigned int i=0; i<chemins.size(); i++) {
            cout<<chemins[i].size()<<flush;
            if ((cheminOK[cheminOK.size()-1]==NULL) || (chemins[i].size()<=cheminOK.size() && (chemins[i][chemins[i].size()-1]!=NULL))) {
                cheminOK=chemins[i];
            }
        }

        return cheminOK;
    }

void Plateau::highlightAttaque(Case* c, int portee) {
    QColor color = Qt::red;
    if (portee==0) {
        color=Qt::transparent;
        portee=m_largeur*m_hauteur;
        c->setBrush(*new QBrush(color));
    }

    for (int i=0; i<=portee; i++) {
        for (int j=0; j<=portee-i; j++) {
            if (i+c->getX()<m_largeur&&j+c->getY()<m_hauteur) {
                if (color==Qt::transparent||porteeAttaquePossible(c, plateau[i+c->getX()][j+c->getY()],portee)) {
                    plateau[i+c->getX()][j+c->getY()]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()-i>=0&&c->getY()-j>=0) {
                if (color==Qt::transparent||porteeAttaquePossible(c, plateau[c->getX()-i][c->getY()-j],portee)) {
                    plateau[c->getX()-i][c->getY()-j]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()+i<m_largeur&&c->getY()-j>=0) {
                if (color==Qt::transparent||porteeAttaquePossible(c, plateau[c->getX()+i][c->getY()-j],portee)) {
                    plateau[c->getX()+i][c->getY()-j]->setBrush(*new QBrush(color));
                }
            }
            if (c->getX()-i>=0&&c->getY()+j<m_hauteur) {
                if (color==Qt::transparent||porteeAttaquePossible(c, plateau[c->getX()-i][c->getY()+j],portee)) {
                    plateau[c->getX()-i][c->getY()+j]->setBrush(*new QBrush(color));
                }
            }
        }
    }
}

bool Plateau::porteeAttaquePossible(Case *c1, Case *c2, int portee) {
    if (c1==NULL)
        return false;
    else if ((c1->getX()==c2->getX())&&(c1->getY()==c2->getY()))
        return true;
    else if (portee==0) {
        return false;
    }

    Case* gauche=NULL;
    Case* droite=NULL;
    Case* avant=NULL;
    Case* arriere=NULL;

    if (c1->getX()<=c2->getX()&&plateau[c1->getX()+1][c1->getY()]->isOccupee())
        droite=plateau[c1->getX()+1][c1->getY()];
    if (c1->getX()>=c2->getX()&&plateau[c1->getX()-1][c1->getY()]->isOccupee())
        gauche=plateau[c1->getX()-1][c1->getY()];
    if (c1->getY()<=c2->getY()&&plateau[c1->getX()][c1->getY()+1]->isOccupee())
        avant=plateau[c1->getX()][c1->getY()+1];
    if (c1->getY()>=c2->getY()&&plateau[c1->getX()][c1->getY()-1]->isOccupee())
        arriere=plateau[c1->getX()][c1->getY()-1];

    return porteeAttaquePossible(droite,c2,portee-1)||porteeAttaquePossible(gauche,c2,portee-1)||porteeAttaquePossible(avant,c2,portee-1)||porteeAttaquePossible(arriere,c2,portee-1);
}
