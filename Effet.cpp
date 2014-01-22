#include "Effet.h"

Effet::Effet(Sort sort, int tour) {
    nbTour = tour;
    m_sort = &sort;    
}

void Effet::decreaseTour() {
    nbTour--;
}