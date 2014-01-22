#ifndef DEF_MAFENETRE
#define DEF_MAFENETRE

#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QPushButton>
#include <QLCDNumber>
#include <QSlider>
#include "QProgressBar"
#include <QMenuBar>
#include <QLineEdit>
#include "regledujeu.h"
#include "QString"
#include "mainwindow.h"

class MaFenetre : public QWidget
{
    Q_OBJECT

    public:
    MaFenetre();

    private:
    QPushButton *m_but;

    QPushButton *m_regles;

    QPushButton *genererPlateau;

    QPushButton *m_2j;

    QLineEdit *PseudoJoueur;
    QPushButton *enregistrer;

    QTabWidget *onglet;
    QWidget *InfoJoueur;
    QWidget *Jouer;

    RegleDuJeu regle;
    MainWindow j2;

    private slots:

    void monAction()
    {
        regle.show();
    }

    void enleverText()
    {
        PseudoJoueur->setText("");
        this->windowTitleChanged("pseudo");
    }

    void afficherJeux2j()
    {
        j2.handleGen();
        j2.handleJouer();
    }

    void enregistrerPseudo()
    {
        this->setWindowTitle(PseudoJoueur->text());
    }

};

#endif
