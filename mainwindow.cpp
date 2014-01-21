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
    Plateau* p=new Plateau();
    QGraphicsView* view = new QGraphicsView(p);
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
    int hauteur = 10;
    int largeur = 15;
    fichier.write((char*)&largeur, sizeof(int));
    fichier.write((char*)&hauteur, sizeof(int));

    catBatiments l = libre;
    //catBatiments t = tour;
    catBatiments c = chateau;
    int size = 1;

    for (int i=0; i<hauteur; i++) {
        for (int j=0; j<largeur; j++) {
            int x=i;
            int y=j;
            fichier.write((char*)&l,sizeof(catBatiments));
            fichier.write((char*)&size,sizeof(int));
            fichier.write((char*)&x,sizeof(int));
            fichier.write((char*)&y,sizeof(int));
        }
    }

    size=2;
    int x=7,y=4;
    fichier.write((char*)&c,sizeof(catBatiments));
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
