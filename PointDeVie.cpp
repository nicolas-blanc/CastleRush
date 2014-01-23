#include "PointDeVie.h"
#include <iostream>
using namespace std;
PointDeVie::PointDeVie(int maxi,int mini)
{
    m_Min = mini;
    m_Max = maxi;
    m_Valeur = maxi;
    m_Bonus = 0;
}

void PointDeVie::modifVie(int val) {
    if ((this->GetValeur() - val) > this->GetMax()){
        m_Valeur = GetMax();}
    else if ((this->GetValeur()-val) <this->GetMin()){
        m_Valeur = GetMin();}
    else {
        this->SetValeur(this->GetValeur() - val);
    }
}
