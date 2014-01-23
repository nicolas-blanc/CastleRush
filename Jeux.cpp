#include "Jeux.h"
#include "Chateau.h"

Jeux::Jeux(int nbrJoueur, string nomPlateau)
{
    m_nbJoueur = nbrJoueur;
    m_FinDePartie = false;

    for(int i = 0; i < nbrJoueur; i++)
        m_Joueur.push_back(new Joueur(i,i));

    setnbTour(0);
    m_Plateau = new Plateau(m_Joueur,nomPlateau);
}

Jeux::~Jeux()
{
    //dtor
}

void Jeux::afficherGraphiqueConsole() {
    // redessinner le plateau + info sur joueur (PA, Pop, num Joueur)
}

void Jeux::partieConsole() {
    int x = 0;
    int y = 0;

    bool finDeTour = false;
    while (!(m_FinDePartie)) {
        m_nbTour++;
        while (!(finDeTour)) {
            int choix = 0;
            cout << "1. Invoquer une unité     2. Choisir une unité     3. Fin de tour" << endl;
            cin >> choix;
            switch (choix) {
            case 1: {
                //Invoquer une unit�
                int unit = 0;
                cout << "1. Guerrier  2. Chevalier  3. Archer  4. Voleur  5. Pretre  6. Mage  7.Annuler" << endl;
                cin >> unit;
                cout << "Donnez la coordonn2e X autour de votre Chateau" << endl;
                cin >> x;
                cout << "Donnez la coordonn2e Y autour de votre Chateau" << endl;
                cin >> y;

                break;}
            case 2:{
                //Deplacer/Attaquer une unit�
                cout << "Donnez la coordonnée X de l'unité" << endl;
                cin >> x;
                cout << "Donnez la coordonnée Y de l'unité" << endl;
                cin >> y;
                Unite * u = (Unite*)m_Plateau->getEntite(x,y); // a rajouter a Plateau => Unite * getUnite(int x, int y); retourne null si pas d'u ou si c'est un batiment
                if (u != NULL) {
                    afficherInfos(u);
                    if (*(u->getJoueur()) == *m_Joueur[m_nbTour%m_nbJoueur]) {
                        int choix2 = 0;
                        cout << "1. Attaquer  2. Deplacer  3. Annuler" << endl;
                        cin >> choix2;
                        switch (choix2) {
                        case 1:
                            cout << "Donnez la coordonnée X de l'unité" << endl;
                            cin >> x;
                            cout << "Donnez la coordonnée Y de l'unité" << endl;
                            cin >> y;
                            u->attaquer(m_Plateau->getCase(x,y));
                            // declencher une exception si un chateau est mort
                            if (testFinDeJeu())
                                throw FinDeJeu();
                            afficherGraphiqueConsole();
                            break;
                        case 2:
                            cout << "Donnez la coordonnée X du nouvel endroit" << endl;
                            cin >> x;
                            cout << "Donnez la coordonnée Y du nouvel endroit" << endl;
                            cin >> y;
                            u->deplacer(m_Plateau->getCase(x,y)); // Modif, voir la fonction dans Unite.cpp
                            afficherGraphiqueConsole();
                            break;
                        default:
                            break;
                        }
                    }
                }
            }
            case 3: {
                finDeTour = true;
                break;}
            default:
                break;
            }
        }
        finDeTour = false;
    }
}

void Jeux::afficherInfos(Unite * ) {
    //affiche en console les informations
}

bool Jeux::testFinDeJeu() {
    bool test = false;
    for(int i = 0; i < m_nbJoueur; i++)
        test = test || m_Joueur[i]->getBatiment()[0]->estMort();
    return test;
}
