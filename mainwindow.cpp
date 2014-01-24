#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "enumerations.h"
#include <iostream>
#include <fstream>

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonGen, SIGNAL(released()), this, SLOT(handleGen()));
    connect(ui->buttonJouer, SIGNAL(released()), this, SLOT(handleJouer()));
}

void MainWindow::handleJouer() {
    m_jeux = new Jeux(2);
    QGraphicsView* view = new QGraphicsView(m_jeux->getPlateau());
    this->hide();
    view->show();
}

void MainWindow::handleGen() {
    if(!is_readable("plateau1.data"))
    {
        fstream fichier("plateau1.data", ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary);

    if (fichier.fail()) { // Si echec de l'ouverture
        //cout << "Impossible d'ouvrir ou de créer le fichier" << endl;
        exit(0);
    }
    int hauteur = 14;
    int largeur = 20;
    fichier.write((char*)&largeur, sizeof(int));
    fichier.write((char*)&hauteur, sizeof(int));

    catBatiments t = tour;
    catBatiments m = magie;
    catBatiments ca = campement;
    catBatiments v = village;
    catBatiments c = chateau;

    int size = 1;
    int joueur = -1;
    //Campement
    int x = 17;
    int y = 1;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&ca,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));
    //village
    x = 2;
    y = 12;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&v,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = 0;
    //tour 1
    x = 5;
    y = 2;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&t,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));
    //tour 2
    x = 2;
    y = 5;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&t,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = 1;
    //tour 1
    x = 17;
    y = 8;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&t,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));
    //tour 2

    x = 14;
    y = 11;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&t,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    size = 2;
    //chateau
    x = 17;
    y = 11;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&c,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = 0;
    //chateau
    x = 1;
    y = 1;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&c,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = -1;
    //Tour de magie
    x = 9;
    y = 6;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&m,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

         popup2 = new QMessageBox;
         popup2->setText("Plateau Généré");
         popup2->exec();

    fichier.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
