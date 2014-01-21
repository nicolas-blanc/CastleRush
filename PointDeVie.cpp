#include "PointDeVie.h"

PointDeVie::PointDeVie(int mini, int maxi)
{
    m_Min = mini;
    m_Max = maxi;
    m_Valeur = maxi;
    m_Bonus = 0;
}

void PointDeVie::modifVie(int val) {
    if ((this->GetValeur() + val) > this->GetMax())
        m_Valeur = GetMax();
    else if ((this->GetValeur() + val) < this->GetMin())
        m_Valeur = m_Min;
    else
        this->SetValeur(this->GetValeur() + val);
}
