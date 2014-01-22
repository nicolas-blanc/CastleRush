#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <fstream>
#include "enumerations.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->buttonGen, SIGNAL(released()), this, SLOT(handleGen()));
    connect(ui->buttonJouer, SIGNAL(released()), this, SLOT(handleJouer()));
}

void MainWindow::handleJouer() {
    try{
        m_jeux = new Jeux(2);
    QGraphicsView* view = new QGraphicsView(m_jeux->getPlateau());
    this->hide();
    view->show();
    }
    catch(exception &e)
    {
        popup2 = new QMessageBox(this);
        popup2->setText("deplacement impossible");
        popup2->exec();
    }
}

void MainWindow::handleGen() {
    fstream fichier("plateau1.data", ios_base::in | ios_base::out | ios_base::trunc | ios_base::binary);

    if (fichier.fail()) { // Si echec de l'ouverture
        cout << "Impossible d'ouvrir ou de créer le fichier" << endl;
        exit(0);
    }
    int hauteur = 14;
    int largeur = 20;
    fichier.write((char*)&largeur, sizeof(int));
    fichier.write((char*)&hauteur, sizeof(int));

    catBatiments l = libre;
    catBatiments t = tour;
    catBatiments m = magie;
    catBatiments ca = campement;
    catBatiments v = village;
    catBatiments c = chateau;

    int size = 1;
    int joueur = -1;
    //Campement
    int x = 5;
    int y = 5;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&ca,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));
    //village
    x = 14;
    y = 8;
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
    x = 17;
    y = 11;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&c,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = 0;
    x = 1;
    y = 1;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&c,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    joueur = -1;
    x = 9;
    y = 6;
    fichier.write((char*)&joueur,sizeof(int));
    fichier.write((char*)&m,sizeof(catBatiments));
    fichier.write((char*)&size,sizeof(int));
    fichier.write((char*)&x,sizeof(int));
    fichier.write((char*)&y,sizeof(int));

    QMessageBox popup(this);
    popup.setText("Plateau généré");
    popup.exec();
    fichier.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}
