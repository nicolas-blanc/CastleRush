#include "Sort.h"

Sort::Sort(string nom, int degat, int portee, int ptAction, int zone) : Attaque(portee,degat,ptAction) {
    m_nomSort=nom;
    this->zone=zone;
}

void Sort::lancerAttaque(Case* ) {
    /*for (int i=0; i<sort.zone; i++) { // /!\ bien gérer toutes les cases de la zone, pas sûr que cet algo marche
        for (int j=0;j<sort.zone;j++) {
            plateau[case.getx+i][case.gety+j].ajouterEffet(sort);
            plateau[case.getx-i][case.gety-j].ajouterEffet(sort);
        }
    }*/
}
