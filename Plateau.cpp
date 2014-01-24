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
#include <QSignalMapper>


#define SIZE 36
#define NBSORT 2


Plateau::Plateau(vector<Joueur*> joueurs, string nomPlateau) : QGraphicsScene() {
    this->setNombreTour(1);
    this->setNombreTourJoueur(1);
    selected=NULL;
    flag=attente;
    nom = NULL;
    mvt = NULL;
    atk = NULL;
    vie = NULL;
    stat = NULL;
    bonus = NULL;
    arch = NULL;
    guer = NULL;
    chev = NULL;
    vol = NULL;
    mag = NULL;
    pret = NULL;

    for(int i = 0; i < NBSORT; i++)
        v_sort.push_back(NULL);
    jserveur = joueurs[0];
    jserveur->setPseudo("Joueur 1");
    jclient = joueurs[1];
    jclient->setPseudo("Joueur 2");
    Batiment* bat;
    ifstream fichierPlateau(nomPlateau.c_str(), ios::in | ios::binary);
        if (fichierPlateau.fail()) { // Si echec de l'ouverture
                cout << "Impossible d'ouvrir ou de créer le fichier" << endl;
                exit(0);
        }
        fichierPlateau.seekg(0,ios_base::beg);

        fichierPlateau.read((char*)&m_largeur ,sizeof(int));
        fichierPlateau.read((char*)&m_hauteur,sizeof(int));
        QPixmap back("images/BackgroundV4.jpg");
        background = new QGraphicsPixmapItem();
        background->setPixmap(back.copy(0,0,SIZE*m_largeur,SIZE*m_hauteur));
        this->addItem(background);

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
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Campement",1);
                                    break;
                            }
                        case village : {
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Village",0);
                            break;
                            }
                        case magie : {
                            bat = new BatimentBonusStat(plateau[x+i][y+j],cases,"Tour de Magie",2);
                            break;
                        }
                        default :
                            break;
                    }
                }
            }
            v_Batiment.push_back(bat);
        }

    TOUR = new QLabel("Tour Total : " + QString::number(NombreTour) + " -- Tour n°" +QString::number(NombreTourJoueur));
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
    connect(sorts,SIGNAL(released()),this,SLOT(handleSort()));

    dep = new QPushButton("Deplacer");
    dep->setToolTip("Permet de deplacer l'unite selectionne.");
    dep->setGeometry(210,SIZE*(m_hauteur+1),80,25);
    addWidget(dep);
    connect(dep, SIGNAL(released()), this, SLOT(handleDep()));

    capt = new QPushButton("Capturer");
    capt->setToolTip("Permet de capturer le batiment à cote de l'unite selectionne.");
    capt->setGeometry(310,SIZE*(m_hauteur+1),80,25);
    addWidget(capt);
    connect(capt, SIGNAL(released()), this, SLOT(handleCapt()));

    /*annuler = new QPushButton("Annuler");
    annuler->setToolTip("Permet d'utiliser l'attaque de base de l'unite selectionne.");
    annuler->setGeometry(410,SIZE*(m_hauteur+1),80,25);
    addWidget(annuler);*/

    fint = new QPushButton("Fin de tour");
    fint->setToolTip("Permet d'utiliser l'attaque de base de l'unite selectionne.");
    fint->setGeometry(510,SIZE*(m_hauteur+1),90,25);
    addWidget(fint);
    connect(fint, SIGNAL(released()), this, SLOT(gestionTour()));

    j.push_back(jserveur);
    j.push_back(jclient);

    jtour = j[0];

    pop = new QProgressBar;
    pop->setGeometry(SIZE*(m_largeur+1), 10, 150, 25);
    PtAction = new QProgressBar;
    PtAction->setGeometry(SIZE*(m_largeur+1), 40, 150, 25);

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

    bonus = new QLabel();
    bonus->setGeometry(SIZE*(m_largeur+1), 100, 150, 25);
    addWidget(bonus);

    stat = new QLabel();
    stat->setGeometry(SIZE*(m_largeur+1), 130, 150, 25);
    addWidget(stat);


    QSignalMapper * mapper = new QSignalMapper();

    for(int i = 0; i < NBSORT; i++) {
        v_sort[i] = new QPushButton("Sort");
        v_sort[i]->setGeometry(SIZE*(m_largeur+1), 220+i*30, 150, 25);
        addWidget(v_sort[i]);
        connect(v_sort[i],SIGNAL(released()),mapper, SLOT(map()));
        mapper->setMapping(v_sort[i],i);
    }

    connect(mapper, SIGNAL(mapped(int)), this, SLOT(handleChoixSort(int)));

    setBoutons(carre);

    for (unsigned int i = 0; i < joueurs.size(); i++) {
        joueurs[i]->liePlateau(this);
    }
}

bool Plateau::isFini(ifstream& fichier) {
    bool aLaFin = fichier.peek()==EOF;
    if (fichier.eof())
        fichier.clear();
    return aLaFin;
}

void Plateau::handleDep() {
        highlight(plateau[0][0]);
        highlight(((Unite*)selected)->getPosition()[0],((Unite*)selected)->getMouvement()+((Unite*)selected)->getJoueur()->getListeBonusJoueur()[4]);
        setFlag(deplacement);
}

void Plateau::gestionTour()
{
    highlight(plateau[0][0]);
    this->setNombreTourJoueur(getNombreTour()/2 + 1);
    pop->setMaximum(jtour->getPopulationMax()+jtour->getListeBonusJoueur()[0]);
    this->setNombreTour(getNombreTour()+1);
    jtour->setPtActionMax(jtour->getPtActionMax()+jtour->getListeBonusJoueur()[1]);
    jtour->setPtAction(jtour->getPtActionMax()+jtour->getListeBonusJoueur()[1]);
    jtour = j[1-jtour->getNumero()];
    this->updatePopPt();
    TOUR->setText("Tours total : " + QString::number(NombreTour) + " -- Tour n°" +QString::number(NombreTourJoueur));
    QMessageBox popup;
    popup.setText("Tour joueur : " + jtour->getPseudo());
    popup.exec();
    for(unsigned int i =0; i<v_Batiment.size(); i++)
    {
        Batiment *batiment = v_Batiment[i];
        if(batiment->Getnom() =="Tour" && batiment->getJoueur() == jtour)
        {
            ((Tour*)v_Batiment[i])->attaqueAuto();
        }
        else if((batiment->Getnom() == "Tour de Magie" || batiment->Getnom() == "Village" || batiment->Getnom() == "Campement") && batiment->getJoueur() == jtour)
        {
             ((BatimentBonusStat*)v_Batiment[i])->modifBonus();
        }
    }

    for(unsigned int i =0; i<((jtour->getUnite()).size()); i++)
    {
        vector<Unite *> vect = jtour->getUnite();
        Unite *unite = vect[i];
        unite->resetMvt();
    }

    if(getInvocateur().size() >0)
    {
        for(unsigned int i =0; i< getInvocateur().size(); i++)
        {
            getBatimentBonus()[i]->changementProprio(getInvocateur()[i]->getJoueur());
            getInvocateur()[i]->setActif(true);
            getBatimentBonus()[i]->getJoueur()->setBatiment(getBatimentBonus()[i]);
        }


        while(Invocateurs.size()!=0)
        {
            Invocateurs.pop_back();
        }

        while(BatimentBonus.size() !=0)
        {
            BatimentBonus.pop_back();
        }
    }
    setBoutons(carre);


    for(unsigned int i = 0; i<j.size();i++)
    {
        for(unsigned int d = 0; d<j[i]->getUnite().size();d++)
        {
            if(j[i]->getUnite()[d]->getVie() == 0)
            {
                    Unite*u= j[i]->getUnite()[d];
                    Case* c = u->getPosition()[0];
                    c->setOccupant(NULL, false);
                    j[i]->deleteUnite(u);
                    u->setPixmap(QPixmap(""));
            }
        }
    }

    for(unsigned int i = 0; i < jtour->getUnite().size(); i++)
        jtour->getUnite()[i]->appliquerEffet();

    for (int i=0; i< m_largeur; i++)
        for (int j=0; j<m_hauteur; j++)
            if(plateau[i][j]->isEffets())
                plateau[i][j]->declencherEffets(jtour);
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
    pop->setMaximum(jtour->getPopulationMax()+jtour->getListeBonusJoueur()[0]);
     pop->setValue(jtour->getPopulation());
     pop->setFormat("Population : %v/%m");
     pop->setAlignment(Qt::AlignCenter);

     PtAction->setValue(jtour->getPtAction());
     PtAction->setMaximum(jtour->getPtActionMax()+jtour->getListeBonusJoueur()[1]);
     PtAction->setFormat("Points d'action : %v/%m");
     PtAction->setAlignment(Qt::AlignCenter);
}


void Plateau::afficheInfoUnite(Entite *u)
{
    mvt->hide();
    atk->hide();
    nom->show();
    nom->setText(QString(u->Getnom().c_str()));
    if(typeid(*u) != typeid(BatimentBonusStat) ){
        vie->show();
        vie->setText("Point de Vie : " + QString::number(u->getVie()));
    }
   if(typeid(*u) == typeid(Chevalier)  ||
            typeid(*u) == typeid(Pretre)     ||
            typeid(*u) == typeid(Magicien)   ||
            typeid(*u) == typeid(Guerrier)   ||
            typeid(*u) == typeid(Voleur)     ||
            typeid(*u) == typeid(Archer))
    {
        mvt->show();
        mvt->setText("Mouvement : " + QString::number(((Unite*)u)->getMouvement()+u->getJoueur()->getListeBonusJoueur()[4]));
        atk->show();
        atk->setText("Attaque : " + QString::number(((Unite*)u)->getAttaqueParDefaut()->getDegat()+((Unite*)u)->getJoueur()->getListeBonusJoueur()[2]));
    }
    if((typeid(*u) == typeid(BatimentBonusStat)))
     {
         stat->show();
         if(((BatimentBonusStat*)u)->getStat()==0)
         stat->setText("Stat : Population");
         else if(((BatimentBonusStat*)u)->getStat()==1)
         stat->setText("Stat : Point d'Action");

         if (u->getJoueur()) {
             if(((BatimentBonusStat*)u)->getStat()==2)
             stat->setText("Stat : Point de Vie");
             else if(((BatimentBonusStat*)u)->getStat()==3)
             stat->setText("Stat : Dégât");
             else if(((BatimentBonusStat*)u)->getStat()==4)
             stat->setText("Stat : Portée");
             else if(((BatimentBonusStat*)u)->getStat()==5)
             stat->setText("Stat : Mouvement");
         }

         bonus->show();
         bonus->setText("Bonus : " + QString::number(((BatimentBonusStat*)u)->getBonus()));
     }
}

void Plateau::handleAtt(){
    highlight(plateau[0][0]);
    highlightAttaque(((Unite*)selected)->getPosition()[0],((Unite*)selected)->getAttaqueParDefaut()->getPortee()+((Unite*)selected)->getJoueur()->getListeBonusJoueur()[3]);
    setFlag(attaque);
}

void Plateau::handleCapt(){
    setFlag(capture);
}

void Plateau::handleSort() {
    int i = 0;
    map <string,Sort*> v_sortMap = ((Unite*)selected)->getSort();
    for( map <string,Sort*>::iterator it = v_sortMap.begin(); it != v_sortMap.end(); it++) {
        v_sort[i]->show();
        v_sort[i]->setText(QString((it->second->getNom()).c_str()));
        i++;
    }
}

void Plateau::handleChoixSort(int i) {

    highlight(plateau[0][0]);
    highlightAttaque(((Unite*)selected)->getPosition()[0],((Unite*)selected)->getSort(i)->getPortee()+((Unite*)selected)->getJoueur()->getListeBonusJoueur()[3]);
    choixSort = ((Unite*)selected)->getSort(i);
    setFlag(attaqueSort);
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
        stat->hide();
        bonus->hide();
        for(int i = 0; i < NBSORT; i++)
            v_sort[i]->hide();
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
        for(int i = 0; i < NBSORT; i++)
            v_sort[i]->hide();
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
        stat->hide();
        bonus->hide();
        for(int i = 0; i < NBSORT; i++)
            v_sort[i]->hide();
        break;
    }
    case (batChateau) : {
        att->hide();
        dep->hide();
        sorts->hide();
        capt->hide();
        vie->show();
        stat->hide();
        bonus->hide();
        if(numJoueur==this->getJoueurTour()->getNumero())
        {
        guer->show();
        mag->show();
        vol->show();
        pret->show();
        chev->show();
        arch->show();
        }
        for(int i = 0; i < NBSORT; i++)
            v_sort[i]->hide();
        break;
    }
    case (unite) : {
        guer->hide();
        mag->hide();
        vol->hide();
        pret->hide();
        chev->hide();
        arch->hide();
        stat->hide();
        bonus->hide();
        att->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        dep->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        sorts->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        capt->setEnabled(numJoueur==this->getJoueurTour()->getNumero());
        setBoutonsUnite(getJoueurTour()->getNumero() == numJoueur);
        for(int i = 0; i < NBSORT; i++)
            v_sort[i]->hide();
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
        capt->setEnabled(false);
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
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
  setUnitInvoc(guerrier);
  setFlag(invoquer);
}
void Plateau::intInvocArc()
{
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
  setUnitInvoc(archer);
  setFlag(invoquer);
}
void Plateau::intInvocChe()
{
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
  setUnitInvoc(chevalier);
  setFlag(invoquer);
}
void Plateau::intInvocMag()
{
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
  setUnitInvoc(magicien);
  setFlag(invoquer);
}
void Plateau::intInvocPre()
{
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
  setUnitInvoc(pretre);
  setFlag(invoquer);
}
void Plateau::intInvocVol()
{
    for (unsigned int i=0; i<((Entite*)getSelect())->getPosition().size(); i++)
        highlight(((Entite*)getSelect())->getPosition()[i],1);
    setUnitInvoc(voleur);
    setFlag(invoquer);
}

void Plateau::highlight(Case* c, int portee, QColor color, bool eraseBlue) {
    QColor blue=Qt::blue;
    blue.setAlpha(126);
    if (portee==-1) {
        color=Qt::transparent;
        portee=m_largeur*m_hauteur;
        for (int i=0; i<m_largeur; i++)
            for (int j=0; j<m_hauteur; j++) {
                if (!plateau[i][j]->getGlyphe()||eraseBlue) {
                    plateau[i][j]->setBrush(*new QBrush(color));
                    if (eraseBlue)
                        plateau[i][j]->setGlyphe(false);
                }
                else {
                    plateau[i][j]->setBrush(*new QBrush(blue));
                }
            }
    }
    else {
        color.setAlpha(126);
        vector<Case*> chemin;
        for (int i=0; i<=portee; i++) {
            for (int j=0; j<=portee-i; j++) {
                if ((i+c->getX()<m_largeur&&j+c->getY()<m_hauteur&&(i+j))||color==blue) {
                    chemin=cheminDeplacement(c, plateau[c->getX()+i][c->getY()+j],portee);
                    if ((color==Qt::transparent||chemin[chemin.size()-1]!=NULL)||color==blue) {
                        plateau[i+c->getX()][j+c->getY()]->setBrush(*new QBrush(color));
                        if (color==blue){plateau[i+c->getX()][j+c->getY()]->setGlyphe(true);}
                    }
                }
                if ((c->getX()-i>=0&&c->getY()-j>=0&&((i+j)||color==blue))) {
                    chemin=cheminDeplacement(c, plateau[c->getX()-i][c->getY()-j],portee);
                    if ((color==Qt::transparent||chemin[chemin.size()-1]!=NULL)||color==blue) {
                        plateau[c->getX()-i][c->getY()-j]->setBrush(*new QBrush(color));
                        if (color==blue) {plateau[c->getX()-i][c->getY()-j]->setGlyphe(true);}
                    }
                }
                if ((c->getX()+i<m_largeur&&c->getY()-j>=0&&((i+j)||color==blue))) {
                    chemin=cheminDeplacement(c, plateau[c->getX()+i][c->getY()-j],portee);
                    if ((color==Qt::transparent||chemin[chemin.size()-1]!=NULL)||color==blue) {
                        plateau[c->getX()+i][c->getY()-j]->setBrush(*new QBrush(color));
                        if (color==blue) {plateau[i+c->getX()][c->getY()-j]->setGlyphe(true);}
                    }
                }
                if ((c->getX()-i>=0&&c->getY()+j<m_hauteur&&((i+j)||color==blue))) {
                    chemin=cheminDeplacement(c, plateau[c->getX()-i][c->getY()+j],portee);
                    if ((color==Qt::transparent||chemin[chemin.size()-1]!=NULL)||color==blue) {
                        plateau[c->getX()-i][c->getY()+j]->setBrush(*new QBrush(color));
                        if (color==blue) {plateau[c->getX()-i][j+c->getY()]->setGlyphe(true);}
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
        if ((cheminOK[cheminOK.size()-1]==NULL) || (chemins[i].size()<=cheminOK.size() && (chemins[i][chemins[i].size()-1]!=NULL))) {
            cheminOK=chemins[i];
        }
    }

    return cheminOK;
}

void Plateau::highlightAttaque(Case* c, int portee, QColor color) {
    if (portee==-1) {
        portee=(m_hauteur>m_largeur?m_hauteur:m_largeur);
        color=Qt::transparent;
    }

    for (int i=0; i<=portee; i++)
        for (int j=0; j<=portee-i; j++) {
            if (c->getX()+i<m_largeur&&c->getY()+j<m_hauteur) {
                plateau[c->getX()+i][c->getY()+j]->setBrush(*new QBrush(color));
            }

            if (c->getX()-i>=0       &&c->getY()+j<m_hauteur)
                plateau[c->getX()-i][c->getY()+j]->setBrush(*new QBrush(color));

            if (c->getX()+i<m_largeur&&c->getY()-j>=0)
                plateau[c->getX()+i][c->getY()-j]->setBrush(*new QBrush(color));

            if (c->getX()-i>=0       &&c->getY()-j>=0)
                plateau[c->getX()-i][c->getY()-j]->setBrush(*new QBrush(color));
        }
}



Unite * Plateau::getUniteAttaqueTour(Tour* tr)
{
    Unite* danger_entite = NULL;
    float distance;
    float distance_danger;
    vector<Unite*> entite_presentes;
    Case* ma_position = tr->getPosition()[0];
    for(int x=0; x<=tr->getAttaque()->getPortee()+tr->getJoueur()->getListeBonusJoueur()[3]; x++)
    {
        for(int y=0; y<=tr->getAttaque()->getPortee()+tr->getJoueur()->getListeBonusJoueur()[3]-x; y++)
        {

            if (ma_position->getX()+x<m_largeur&&ma_position->getY()+y<m_hauteur)
            {

                Case* caseoccupee = plateau[ma_position->getX()+x][ma_position->getY()+y];
                if(caseoccupee->isOccupee()  && (caseoccupee->getOccupant()->Getnom() == "Chevalier"||caseoccupee->getOccupant()->Getnom() == "Archer"||caseoccupee->getOccupant()->Getnom() == "Guerrier"||caseoccupee->getOccupant()->Getnom() == "Magicien"||caseoccupee->getOccupant()->Getnom() == "Pretre"||caseoccupee->getOccupant()->Getnom() == "Voleur"))
                {
                    entite_presentes.push_back((Unite*)(caseoccupee->getOccupant()));
                }
            }

            if (x!=0&&ma_position->getX()-x>=0&&ma_position->getY()+y<m_hauteur)
            {
                Case* caseoccupee = plateau[ma_position->getX()-x][ma_position->getY()+y];
                if(caseoccupee->isOccupee()  && (caseoccupee->getOccupant()->Getnom() == "Chevalier"||caseoccupee->getOccupant()->Getnom() == "Archer"||caseoccupee->getOccupant()->Getnom() == "Guerrier"||caseoccupee->getOccupant()->Getnom() == "Magicien"||caseoccupee->getOccupant()->Getnom() == "Pretre"||caseoccupee->getOccupant()->Getnom() == "Voleur"))
                {
                    entite_presentes.push_back((Unite*)(caseoccupee->getOccupant()));
                }
            }
            if (ma_position->getX()+x<m_largeur&&ma_position->getY()-y>=0)
            {
                Case* caseoccupee = plateau[ma_position->getX()+x][ma_position->getY()-y];
                if(caseoccupee->isOccupee()  && (caseoccupee->getOccupant()->Getnom() == "Chevalier"||caseoccupee->getOccupant()->Getnom() == "Archer"||caseoccupee->getOccupant()->Getnom() == "Guerrier"||caseoccupee->getOccupant()->Getnom() == "Magicien"||caseoccupee->getOccupant()->Getnom() == "Pretre"||caseoccupee->getOccupant()->Getnom() == "Voleur"))
                {
                    entite_presentes.push_back((Unite*)(caseoccupee->getOccupant()));
                }
            }
            if (x!=0&&ma_position->getX()-x>=0&&ma_position->getY()-y>=0)
            {
                Case* caseoccupee = plateau[ma_position->getX()-x][ma_position->getY()-y];
                if(caseoccupee->isOccupee()  && (caseoccupee->getOccupant()->Getnom() == "Chevalier"||caseoccupee->getOccupant()->Getnom() == "Archer"||caseoccupee->getOccupant()->Getnom() == "Guerrier"||caseoccupee->getOccupant()->Getnom() == "Magicien"||caseoccupee->getOccupant()->Getnom() == "Pretre"||caseoccupee->getOccupant()->Getnom() == "Voleur"))
                {
                    entite_presentes.push_back((Unite*)(caseoccupee->getOccupant()));
                }
            }
        }
    }

    if(entite_presentes.size()>0)
    {
        Unite* u = entite_presentes[0];
        Case* c =u->getPosition()[0];
        distance_danger = abs(tr->getJoueur()->getBatiment()[0]->getPosition()[0]->getX()-
                               c->getX())
                                + abs(tr->getJoueur()->getBatiment()[0]->getPosition()[0]->getY()-
                                c->getY());
        danger_entite = entite_presentes[0];
        for(unsigned int i =1; i<entite_presentes.size(); i++)
        {
            cout<<"lol1"<<flush;
            u = entite_presentes[i];
            c =u->getPosition()[0];
            distance = abs(tr->getJoueur()->getBatiment()[0]->getPosition()[0]->getX()-
                    c->getX())
                     + abs(tr->getJoueur()->getBatiment()[0]->getPosition()[0]->getY()-
                     c->getY());
            cout<<"lol2"<<flush;
            if(distance<distance_danger&&u->getJoueur()->getNumero()!=tr->getJoueur()->getNumero())
            {
                distance_danger = distance;
                danger_entite = entite_presentes[i];
            }
        }
    }

    //if (danger_entite->getJoueur()->getNumero()==tr->getJoueur()->getNumero()) danger_entite=NULL;

    return danger_entite;
}

void Plateau::CapturePossible(Case *c)
{
    if(((c->getX()+1<m_largeur)&&(plateau[c->getX()+1][c->getY()]&& plateau[c->getX()+1][c->getY()]->isOccupee()&&(plateau[c->getX()+1][c->getY()]->getOccupant()->Getnom()=="Tour de Magie"
                                                                                                 ||plateau[c->getX()+1][c->getY()]->getOccupant()->Getnom()=="Campement"
                                                                                                 ||plateau[c->getX()+1][c->getY()]->getOccupant()->Getnom()=="Village")))
            || (((c->getX()-1>=0)&&plateau[c->getX()-1][c->getY()]&& plateau[c->getX()-1][c->getY()]->isOccupee()&&(plateau[c->getX()-1][c->getY()]->getOccupant()->Getnom()=="Tour de Magie"
                                                                                                 ||plateau[c->getX()-1][c->getY()]->getOccupant()->Getnom()=="Campement"
                                                                                                 ||plateau[c->getX()-1][c->getY()]->getOccupant()->Getnom()=="Village")))
            || (((c->getY()+1<m_hauteur)&&plateau[c->getX()][c->getY()+1]&& plateau[c->getX()][c->getY()+1]->isOccupee()&&(plateau[c->getX()][c->getY()+1]->getOccupant()->Getnom()=="Tour de Magie"
                                                                                                 ||plateau[c->getX()][c->getY()+1]->getOccupant()->Getnom()=="Campement"
                                                                                                 ||plateau[c->getX()][c->getY()+1]->getOccupant()->Getnom()=="Village")))
            || ((c->getY()-1>=0)&&(plateau[c->getX()][c->getY()-1]&& plateau[c->getX()][c->getY()-1]->isOccupee()&&(plateau[c->getX()][c->getY()-1]->getOccupant()->Getnom()=="Tour de Magie"
                                                                                                 ||plateau[c->getX()][c->getY()-1]->getOccupant()->Getnom()=="Campement"
                                                                                                 ||plateau[c->getX()][c->getY()-1]->getOccupant()->Getnom()=="Village"))))
    {
        capt->setEnabled(true);
    }
    else
    {
        capt->setEnabled(false);
    }

}

void Plateau::finDuJeu()
{

    for(int x =0; x<m_largeur;x++)
        for(int y =0; y<m_hauteur;y++)
        {
            plateau[x][y]->setFlag(QGraphicsItem::ItemIsSelectable,false);
        }
    for(unsigned int i =0; i<j.size();i++)
    {
        for(unsigned int a =0; a<j[i]->getUnite().size(); a++)
        {
            j[i]->getUnite()[a]->setFlag(QGraphicsItem::ItemIsSelectable,false);
        }
    }

    for(unsigned int i =0; i<v_Batiment.size();i++)
    {
        v_Batiment[i]->setFlag(QGraphicsItem::ItemIsSelectable,false);
    }

    this->setBoutons(carre);
    fint->hide();
}
