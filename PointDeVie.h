#ifndef POINTDEVIE_H
#define POINTDEVIE_H


class PointDeVie
{
    public:
        PointDeVie(int maxi,int mini);
        inline int GetMin() { return m_Min; }
        inline int GetMax() { return m_Max + m_Bonus; }
        inline int GetValeur() { return m_Valeur; }
        inline void SetValeur(int val) {m_Valeur = val;}

        void modifVie(int val);
    protected:
    private:
        int m_Min;
        int m_Max;
        int m_Valeur;
        int m_Bonus;
};

#endif // POINTDEVIE_H
