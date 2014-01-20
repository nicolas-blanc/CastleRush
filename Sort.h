#ifndef SORT_H
#define	SORT_H

#include <string>

#include "Attaque.h"

using namespace std;

class Sort : public Attaque {
public:
    Sort(string nom, int degat = 1, int portee = 1, int ptAction = 1, int zone = 1);
    void lancerAttaque(Case* c);

private:
    string m_nomSort;
    int zone;
};
#endif	/* SORT_H */

