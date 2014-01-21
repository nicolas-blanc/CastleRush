#include "regledujeu.h"
#include <QTabBar>

RegleDuJeu::RegleDuJeu()
{

    setFixedSize(800, 400);
    this->setWindowTitle("Regle Du Jeu");
    m_fermer = new QPushButton("Fermer", this);
    m_fermer->move(700,365);
    QObject::connect(m_fermer, SIGNAL(clicked()), this, SLOT(close()));

    //ONGLETREGLES

    ongletRegles = new QTabWidget(this);
    ongletRegles->setGeometry(30, 20, 740, 340);

    //InfoJeux
    IJ= new QWidget;
    QGridLayout *vbox1 = new QGridLayout;
    InfoJeux = new QLabel("- Chaque joueur joue chacun leur tour. Le tour se termine lorsqu’un jouer n’a plus de points d’actions\n"
                          "   ou que celui-ci décide de mettre fin à son tour.\n\n"

                          "- Le but du jeu est de réduire les points de vie du château adverse à zéro.\n\n"

                          "- Dans ce but, chaque joueur peut utiliser différents types de personnages qu’ils peuvent invoquer\n   "
                          "chaque tour dans la limite de leur jauge de population et de leur jauge d’action.\n\n"

                          "- Chaque joueur a la possibilité de capturer différents bâtiments présents sur la carte, qui lui confèrent\n   "
                          "différents bonus.");
    vbox1->addWidget(InfoJeux);
    IJ->setLayout(vbox1);
    //InfoJeux

    //Déroulement d'un Tour
    DT= new QWidget;
    QGridLayout *vbox5 = new QGridLayout;
    DeroulementTour = new QLabel("- Le joueur est prévenu du début de son tour.\n\n"
                                 "- Les captures réussies sont annoncées.\n\n"
                                 "- Ses jauges de population et d’actions sont mises à jour.\n\n"
                                 "- Les résultats des effets présents sur la carte sont annoncés.\n\n"
                                 "- Le joueur est alors libre d’effectuer les actions de sont choix.\n\n"
                                 "- Lorsque le joueur a sa jauge d’action vide, ou qu’il choisit de mettre fin à son tour avec l’option associée,\n   "
                                 "le joueur suivant est prévenu du début de son tour qui se déroule de la même manière et ainsi de suite\n   "
                                 "jusqu’ a la fin du jeu.");
    vbox5->addWidget(DeroulementTour);
    DT->setLayout(vbox5);
    //Déroulement d'un Tour

    //Map
    MAP= new QWidget;
    QGridLayout *vbox29 = new QGridLayout;
    Map = new QPushButton("");
    Map->setIcon(QIcon("images/Plateau.JPG"));
    Map->setIconSize(QSize(190,169));
    Map->setMaximumSize(QSize(190,169));
    Map->setToolTip("Agrandir");
    Map->setCursor(Qt::PointingHandCursor);
    Map->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox29->addWidget(Map);
    MAP->setLayout(vbox29);
    //Map

    ongletRegles->addTab(IJ, "Fonctionnement");
    ongletRegles->addTab(DT, "Déroulement");
    ongletRegles->addTab(MAP, "Map");

    QObject::connect(Map, SIGNAL(clicked()), this, SLOT(agrandirMap()));

    //ONGLETREGLES




    //ONGLETJAUGE

    JAU =new QWidget;
    QGridLayout *vbox14 = new QGridLayout;
    Jauge = new QTabWidget(this);
    Jauge->setGeometry(50, 40, 680, 280);
    vbox14->addWidget(Jauge);
    JAU->setLayout(vbox14);

    //Jauge d'actions
    JA= new QWidget;
    QGridLayout *vbox2 = new QGridLayout;
    JaugeAction = new QLabel("Chaque joueur possède nombre de points d’actions qui augmente a chaque tour, Cependant\n"
                             "toutes les actions possibles durant un tour(Attaque, déplacements d’unités...) consomment\n"
                             "un certains nombres de points.");
    vbox2->addWidget(JaugeAction);
    JA->setLayout(vbox2);
    //Jauge d'actions

    //Jauge de Population
    JP= new QWidget;
    QGridLayout *vbox3 = new QGridLayout;
    JaugePopulation = new QLabel("Chaque joueur possède un nombre limite d’unités, chaque unité coûtant un certains nombres de points\n"
                                 "de population en fonction de sa puissance. Lorsque la limite de population est atteinte un joueur\n"
                                 "ne peut plus invoquer.");
    vbox3->addWidget(JaugePopulation);
    JP->setLayout(vbox3);
    //Jauge de Population

    ongletRegles->addTab(JAU, "Jauges");
    Jauge->addTab(JA, "Action");
    Jauge->addTab(JP, "Population");

    //ONGLETJAUGE




    //BATIMENTS

    //Info Batiments
    BATS= new QWidget;
    QGridLayout *vbox4 = new QGridLayout;
    IBatiments = new QLabel("Le plateau de jeu comporte plusieurs bâtiments capturables ou non par chacun des joueurs.\n\n");
    vbox4->addWidget(IBatiments);
    BATS->setLayout(vbox4);
    //Info Batiments

    BAT =new QWidget;
    Batiments = new QTabWidget(this);
    Batiments->setGeometry(50, 40, 680, 280);
    vbox4->addWidget(Batiments);
    BAT->setLayout(vbox4);


    //BATIMENTCAPTURABLES

    BC =new QWidget;
    QGridLayout *vbox15 = new QGridLayout;
    BatimentCapturable = new QTabWidget(this);
    BatimentCapturable->setGeometry(70, 60, 620, 220);
    vbox15->addWidget(BatimentCapturable);
    BC->setLayout(vbox15);

    //Camp d'entrainement
    CE= new QWidget;
    QGridLayout *vbox17 = new QGridLayout;
    CampEntrainement = new QLabel("Augmente le nombre de points d’actions disponibles chaque tour.");
    vbox17->addWidget(CampEntrainement);

    CampEntrainementIMG = new QPushButton("");
    CampEntrainementIMG->setIcon(QIcon("images/CampEntrainement.png"));
    CampEntrainementIMG->setIconSize(QSize(76,68));
    CampEntrainementIMG->clicked(false);
    CampEntrainementIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox17->addWidget(CampEntrainementIMG);

    CE->setLayout(vbox17);
    //Camp d'entrainement

    //Village
    VIL= new QWidget;
    QGridLayout *vbox18 = new QGridLayout;
    Village = new QLabel("Augmente le nombre limite de population du joueur.");
    vbox18->addWidget(Village);

    VillageIMG = new QPushButton("");
    VillageIMG->setIcon(QIcon("images/Village.png"));
    VillageIMG->setIconSize(QSize(80,69));
    VillageIMG->clicked(false);
    VillageIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox18->addWidget(VillageIMG);

    VIL->setLayout(vbox18);
    //Village

    //Chateau Bonus
    CB= new QWidget;
    QGridLayout *vbox19 = new QGridLayout;
    ChateauBonus = new QLabel("Château au centre de la carte: Donne un bonus aléatoire a chaque capture. Le bonus gagne en\n"
                              "puissance en fonction de la durée de possession du château.");
    vbox19->addWidget(ChateauBonus);

    ChateauBonusIMG = new QPushButton("");
    ChateauBonusIMG->setIcon(QIcon("images/ChateauBonus.png"));
    ChateauBonusIMG->setIconSize(QSize(57,55));
    ChateauBonusIMG->clicked(false);
    ChateauBonusIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox19->addWidget(ChateauBonusIMG);

    CB->setLayout(vbox19);
    //Chateau Bonus

    //BATIMENTCAPTURABLES


    //BATIMENTNONCAPTURABLES

    BNC =new QWidget;
    QGridLayout *vbox16 = new QGridLayout;
    BatimentNonCapturable = new QTabWidget(this);
    BatimentNonCapturable->setGeometry(70, 60, 620, 220);
    vbox16->addWidget(BatimentNonCapturable);
    BNC->setLayout(vbox16);

    //Chateau
    CHA= new QWidget;
    QGridLayout *vbox20 = new QGridLayout;
    Chateau = new QLabel("Bâtiment puissant permettant d’invoquer depuis un nouvel endroit de la carte.");
    vbox20->addWidget(Chateau);

    ChateauIMG = new QPushButton("");
    ChateauIMG->setIcon(QIcon("images/Chateau.png"));
    ChateauIMG->setIconSize(QSize(62,64));
    ChateauIMG->clicked(false);
    ChateauIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox20->addWidget(ChateauIMG);

    CHA->setLayout(vbox20);
    //Chateau

    //Tour
    TR= new QWidget;
    QGridLayout *vbox21 = new QGridLayout;
    Tour = new QLabel("Plusieurs tours sont disponible pour chaque joueur. Elle attaque automatquement l'unité le\n"
                      "plus pret du chateau qui est dans son périmètre d'attaque.");
    vbox21->addWidget(Tour);

    TourIMG = new QPushButton("");
    TourIMG->setIcon(QIcon("images/Tour.png"));
    TourIMG->setIconSize(QSize(50,50));
    TourIMG->clicked(false);
    TourIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox21->addWidget(TourIMG);

    TR->setLayout(vbox21);
    //Tour

    //BATIMENTNONCAPTURABLES

    ongletRegles->addTab(BAT, "Batiments");
    Batiments->addTab(BC, "Capturables");
    Batiments->addTab(BNC, "Non Capturables");
    BatimentCapturable->addTab(CE, "Camp Entrainement");
    BatimentCapturable->addTab(VIL, "Village");
    BatimentCapturable->addTab(CB, "Chateau Bonus");
    BatimentNonCapturable->addTab(CHA, "Chateau");
    BatimentNonCapturable->addTab(TR, "Tour");

    //BATIMENTS




    //ONGLETCOMMANDES

    COM= new QWidget;
    QGridLayout *vbox6 = new QGridLayout;
    Commandes = new QTabWidget(this);
    Commandes->setGeometry(50, 40, 680, 280);
    vbox6->addWidget(Commandes);
    COM->setLayout(vbox6);

    //Selectionner une unité
    SU= new QWidget;
    QGridLayout *vbox7 = new QGridLayout;
    CommandeSelectUnite = new QLabel("- Cliquez simplement sur l’unité que vous souhaitez sélectionnée.");
    vbox7->addWidget(CommandeSelectUnite);
    SU->setLayout(vbox7);
    //Selectionner une unité

    //Choix d'une Action
    CA= new QWidget;
    QGridLayout *vbox8 = new QGridLayout;
    CommandeChoixAction = new QLabel("- Après avoir sélectionné une unité, cliquez sur l’action de votre choix dans le menu.");
    vbox8->addWidget(CommandeChoixAction);
    CA->setLayout(vbox8);
    //Choix d'une Action

    //Attaquer
    ATK= new QWidget;
    QGridLayout *vbox9 = new QGridLayout;
    CommandeAttaquer = new QLabel("- Lors de la sélection de cette commande, la portée d’attaque de l’unité sélectionnée s’affiche,\n   "
                                  "cliquez ensuite sur une case disponible et votre unité attaquera la case ciblée. Attention l’unité suivra\n   "
                                  "vos ordres à la lettre et peut donc attaquer une case vide. Après avoir attaquer une unité ne peut plus\n "
                                  "  se déplacer durant le tour en cour.");
    vbox9->addWidget(CommandeAttaquer);
    ATK->setLayout(vbox9);
    //Attaquer

    //Sorts
    SOR= new QWidget;
    QGridLayout *vbox10 = new QGridLayout;
    CommandeSorts = new QLabel("- Permet d’accéder aux sorts que possède l’unité, sélectionné en un et sa portée s’affiche.\n   "
                               "Il ne vous reste plus qu’a sélectionné une cible et votre unité lancera son sort. Une unité peut lancer\n "
                               "  un nombre illimité de sorts (Dans la limite de la jauge d’actions).");
    vbox10->addWidget(CommandeSorts);
    SOR->setLayout(vbox10);
    //Sorts

    //Déplacement
    DEP= new QWidget;
    QGridLayout *vbox11 = new QGridLayout;
    CommandeDeplacement = new QLabel("- En sélectionnant cette option, les cases sur lesquels votre unité peut se déplacer s’affiche,\n   "
                                     "sélectionné en une et votre unité si rendra. Chaque unité ne peut réaliser cette action qu’une fois\n   "
                                     "par tour.");

    vbox11->addWidget(CommandeDeplacement);

    CommandeDeplacementIMG = new QPushButton("");
    CommandeDeplacementIMG->setIcon(QIcon("images/deplacer.png"));
    CommandeDeplacementIMG->setIconSize(QSize(190,169));
    CommandeDeplacementIMG->setMaximumSize(QSize(190,169));
    CommandeDeplacementIMG->setToolTip("Agrandir");
    CommandeDeplacementIMG->setCursor(Qt::PointingHandCursor);
    CommandeDeplacementIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox11->addWidget(CommandeDeplacementIMG);

    DEP->setLayout(vbox11);
    //Déplacements

    //Informations Unité Adverse
    IUA= new QWidget;
    QGridLayout *vbox12 = new QGridLayout;
    CommandeInfoUniteAdverse = new QLabel("- Un clic sur une unité adverse vous permet d’obtenir ses statistiques(point de vie, portée, ...).");
    vbox12->addWidget(CommandeInfoUniteAdverse);

    CommandeInfoUniteAdverseIMG = new QPushButton("");
    CommandeInfoUniteAdverseIMG->setIcon(QIcon("images/infoAdversaire.png"));
    CommandeInfoUniteAdverseIMG->setIconSize(QSize(190,169));
    CommandeInfoUniteAdverseIMG->setMaximumSize(QSize(190,169));
    CommandeInfoUniteAdverseIMG->setToolTip("Agrandir");
    CommandeInfoUniteAdverseIMG->setCursor(Qt::PointingHandCursor);
    CommandeInfoUniteAdverseIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox12->addWidget(CommandeInfoUniteAdverseIMG);

    IUA->setLayout(vbox12);
    //Informations Unité Adverse

    //Capturer
    CAP= new QWidget;
    QGridLayout *vbox13 = new QGridLayout;
    CommandeCapturer = new QLabel("- Lorsque une unité se trouve dans la zone de capture d’un bâtiment la commande “Capturer”\n   "
                                  "s’ajoute au menu. En sélectionnant celle-ci votre unité capturera le bâtiment mais ne pourra effectuer\n "
                                  "  aucune autre action durant ce tour. Attention :: si l’unité ayant réalisé l’action meurt ou que l’adversaire\n   "
                                  "lance lui aussi une capture sur le même bâtiment, le joueur ne prendra possession du bâtiment\n   "
                                  "le tour suivant.");
    vbox13->addWidget(CommandeCapturer);
    CAP->setLayout(vbox13);
    //Capturer

    ongletRegles->addTab(COM, "Commandes");
    Commandes->addTab(SU, "Selection Unité");
    Commandes->addTab(CA, "Action");
    Commandes->addTab(ATK, "Attaquer");
    Commandes->addTab(SOR, "Sorts");
    Commandes->addTab(DEP, "Déplacement");
    Commandes->addTab(IUA, "Info Adversaire");
    Commandes->addTab(CAP, "Capturer");

    QObject::connect(CommandeDeplacementIMG, SIGNAL(clicked()), this, SLOT(agrandirDep()));
    QObject::connect(CommandeInfoUniteAdverseIMG, SIGNAL(clicked()), this, SLOT(agrandirInfoUnite()));

    //ONGLETCOMMANDES




    //ONGLETUNITES

    UNI= new QWidget;
    QGridLayout *vbox22 = new QGridLayout;
    Unites = new QTabWidget(this);
    Unites->setGeometry(50, 40, 680, 280);
    vbox22->addWidget(Unites);
    UNI->setLayout(vbox22);

    //Archer

    AR= new QWidget;
    QGridLayout *vbox23 = new QGridLayout;
    Archer = new QLabel("L'archer est une unité basique qui a des attaques de longue distance.\n\n"
                        "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                        "Atk:: 1     Coût::1");
    vbox23->addWidget(Archer);

    ArcherIMG = new QPushButton("");
    ArcherIMG->setIcon(QIcon("images/Archer.png"));
    ArcherIMG->setIconSize(QSize(100,130));
    ArcherIMG->clicked(false);
    ArcherIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox23->addWidget(ArcherIMG);

    AR->setLayout(vbox23);

    //Archer

    //Chevalier

    CHE= new QWidget;
    QGridLayout *vbox24 = new QGridLayout;
    Chevalier = new QLabel("Le chavalier est une untié puissante avec de fortes attaques,"
                           "mais elle coûte plus cher en point d'action.\n\n"
                           "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                           "Atk:: 1     Coût::1");
    vbox24->addWidget(Chevalier);

    ChevalierIMG = new QPushButton("");
    ChevalierIMG->setIcon(QIcon("images/Chevalier.png"));
    ChevalierIMG->setIconSize(QSize(100,130));
    ChevalierIMG->clicked(false);
    ChevalierIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox24->addWidget(ChevalierIMG);

    CHE->setLayout(vbox24);

    //Chevalier

    //Guerrier

    GUE= new QWidget;
    QGridLayout *vbox25 = new QGridLayout;
    Guerrier = new QLabel("Le guerrier est une unité sans grande valeur, mais elle ne coûte pas beaucoup en point d'action.\n\n"
                          "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                          "Atk:: 1     Coût::1");
    vbox25->addWidget(Guerrier);

    GuerrierIMG = new QPushButton("");
    GuerrierIMG->setIcon(QIcon("images/Guerrier.png"));
    GuerrierIMG->setIconSize(QSize(100,130));
    GuerrierIMG->clicked(false);
    GuerrierIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox25->addWidget(GuerrierIMG);

    GUE->setLayout(vbox25);

    //Guerrier

    //Voleur

    VOL= new QWidget;
    QGridLayout *vbox26 = new QGridLayout;
    Voleur = new QLabel("Le voleur est une unité puissante qui a des sorts sympathique.\n\n"
                        "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                        "Atk:: 1     Coût::1");
    vbox26->addWidget(Voleur);

    VoleurIMG = new QPushButton("");
    VoleurIMG->setIcon(QIcon("images/Voleur.png"));
    VoleurIMG->setIconSize(QSize(100,130));
    VoleurIMG->clicked(false);
    VoleurIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox26->addWidget(VoleurIMG);

    VOL->setLayout(vbox26);

    //Voleur

    //Pretre

    PRE= new QWidget;
    QGridLayout *vbox27 = new QGridLayout;
    Pretre = new QLabel("Le pretre est une unité de soutien, qui peut soigné ou aidé les autres unités du joueur.\n\n"
                        "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                        "Atk:: 1     Coût::1");
    vbox27->addWidget(Pretre);

    PretreIMG = new QPushButton("");
    PretreIMG->setIcon(QIcon("images/Pretre.png"));
    PretreIMG->setIconSize(QSize(100,130));
    PretreIMG->clicked(false);
    PretreIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox27->addWidget(PretreIMG);

    PRE->setLayout(vbox27);

    //Pretre

    //Magicien

    MAG= new QWidget;
    QGridLayout *vbox28 = new QGridLayout;
    Magicien = new QLabel("Le magicien est une unité puissante qui a des sorts de longue distance, et des sorts d'AOE.\n\n"
                          "Vie:: 1     Portée:: 1      Mouvement:: 1\n"
                          "Atk:: 1     Coût::1");
    vbox28->addWidget(Magicien);

    MagicienIMG = new QPushButton("");
    MagicienIMG->setIcon(QIcon("images/Magicien.png"));
    MagicienIMG->setIconSize(QSize(100,130));
    MagicienIMG->clicked(false);
    MagicienIMG->setStyleSheet("QPushButton\
    {\
        border: 0px;\
        background: none;\
        color: gray;\
    }\
    \
    QPushButton:checked\
    {\
        color: black;\
    }");
    vbox28->addWidget(MagicienIMG);

    MAG->setLayout(vbox28);

    //Magicien

    ongletRegles->addTab(UNI, "Unités");
    Unites->addTab(AR, "Archer");
    Unites->addTab(CHE, "Chevalier");
    Unites->addTab(GUE, "Guerrier");
    Unites->addTab(VOL, "Voleur");
    Unites->addTab(PRE, "Pretre");
    Unites->addTab(MAG, "Magicien");

    //ONGLETUNITES
}
