#include "mafenetre.h"
#include <QVBoxLayout>
#include <QtGui>


MaFenetre::MaFenetre() : QWidget()
{
    setFixedSize(300, 300);

    m_but = new QPushButton("Quitter", this);
    m_but->move(200,250);

    m_regles = new QPushButton("Regle du jeu", this);
    m_regles->move(90,200);

    QTabWidget *onglet = new QTabWidget(this);
    onglet->setGeometry(30, 20, 240, 160);


    InfoJoueur = new QWidget;
    Jouer= new QWidget;

    //Jouer

    m_2j= new QPushButton("Partie 2 joueurs");

    QVBoxLayout *vbox1 = new QVBoxLayout;
    vbox1->addWidget(m_2j);

    Jouer->setLayout(vbox1);

    //Jouer

    //Info Joueur

    enregistrer= new QPushButton("Enregistrer");
    PseudoJoueur = new QLineEdit("Entrez votre pseudo");

    QVBoxLayout *vbox2 = new QVBoxLayout;
    vbox2->addWidget(PseudoJoueur);
    vbox2->addWidget(enregistrer);

    InfoJoueur->setLayout(vbox2);

    //Info Joueur

    onglet->addTab(InfoJoueur, "Info");
    onglet->addTab(Jouer, "Jouer");

    QObject::connect(m_regles, SIGNAL(clicked()), this, SLOT(monAction()));
    QObject::connect(m_but, SIGNAL(clicked()), qApp, SLOT(quit()));
    QObject::connect(PseudoJoueur, SIGNAL(selectionChanged()), this, SLOT(enleverText()));
    QObject::connect(m_2j, SIGNAL(clicked()), this, SLOT(afficherJeux2j()));
    QObject::connect(enregistrer, SIGNAL(clicked()), this, SLOT(enregistrerPseudo()));
}
