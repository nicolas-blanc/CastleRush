#include "editeur.h"

Editeur::Editeur()
{
        fstream fichier("plateau1.data", ios_base::in | ios_base::out | ios_base::app | ios_base::binary);

        if (fichier.fail()) { // Si echec de l'ouverture
            cout << "Impossible d'ouvrir ou de créer le fichier" << endl;
            exit(0);
        }
        int hauteur = 10;
        int largeur = 15;
        fichier.write((char*)&largeur, sizeof(int));
        fichier.write((char*)&hauteur, sizeof(int));

        catBatiments l = libre;
        catBatiments t = tour;
        catBatiments c = chateau;
        int size = 1;

        for (int i=0; i<hauteur; i++) {
            for (int j=0; j<largeur; j++) {
                int x=i;
                int y=j;
                fichier.write((char*)&l,sizeof(catBatiments));
                fichier.write((char*)&size,sizeof(int));
                fichier.write((char*)&x,sizeof(catBatiments));
                fichier.write((char*)&y,sizeof(catBatiments));
            }
        }

        size=4;
        int x=7,y=4;
        fichier.write((char*)&c,sizeof(catBatiments));
        fichier.write((char*)&size,sizeof(int));
        fichier.write((char*)&x,sizeof(catBatiments));
        fichier.write((char*)&y,sizeof(catBatiments));

        return 0;
}
