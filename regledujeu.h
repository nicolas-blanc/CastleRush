#ifndef REGLEDUJEU_H
#define REGLEDUJEU_H

#include <QApplication>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QTabWidget>
#include <QVBoxLayout>

class RegleDuJeu : public QWidget
{

    Q_OBJECT

public:
    RegleDuJeu();

private :
    QTabWidget *ongletRegles;
    QLabel *InfoJeux;
    QLabel *DeroulementTour;

    QTabWidget *Jauge;
    QLabel *JaugeAction;
    QLabel *JaugePopulation;

    QTabWidget *Batiments;
    QLabel *IBatiments;
    QTabWidget *BatimentCapturable;
    QTabWidget *BatimentNonCapturable;
    QLabel *CampEntrainement;
    QPushButton * CampEntrainementIMG;
    QLabel *Village;
    QPushButton *VillageIMG;
    QLabel *ChateauBonus;
    QPushButton *ChateauBonusIMG;
    QLabel *Chateau;
    QPushButton *ChateauIMG;
    QLabel *Tour;
    QPushButton *TourIMG;

    QTabWidget *Commandes;
    QLabel *CommandeSelectUnite;
    QLabel *CommandeChoixAction;
    QLabel *CommandeAttaquer;
    QLabel *CommandeSorts;
    QLabel *CommandeDeplacement;
    QLabel *CommandeInfoUniteAdverse;
    QLabel *CommandeCapturer;

    QTabWidget *Unites;
    QLabel *Archer;
    QPushButton *ArcherIMG;
    QLabel *Guerrier;
    QPushButton *GuerrierIMG;
    QLabel *Chevalier;
    QPushButton *ChevalierIMG;
    QLabel *Voleur;
    QPushButton *VoleurIMG;
    QLabel *Pretre;
    QPushButton *PretreIMG;
    QLabel *Magicien;
    QPushButton *MagicienIMG;

    QPushButton *m_fermer;

     QWidget * IJ;
     QWidget * JAU;
     QWidget * JA;
     QWidget * JP;
     QWidget * BATS;
     QWidget * BAT;
     QWidget * BC;
     QWidget * BNC;
     QWidget * CE;
     QWidget * VIL;
     QWidget * CB;
     QWidget * CHA;
     QWidget * TR;
     QWidget * DT;
     QWidget * COM;
     QWidget * SU;
     QWidget * CA;
     QWidget * ATK;
     QWidget * SOR;
     QWidget * DEP;
     QWidget * IUA;
     QWidget * CAP;
     QWidget * UNI;
     QWidget * AR;
     QWidget * CHE;
     QWidget * GUE;
     QWidget * VOL;
     QWidget * PRE;
     QWidget * MAG;

};

#endif // REGLEDUJEU_H
