#ifndef NEWTSP_H
#define NEWTSP_H

#include "parameter.h"
#include "Ant.h"


class NewTSP
{
    public:
        void InitData();
        void TSPSearch();
        void UpdatePheromone();
        void DistanceInit();
        bool CalcMaxMinPheromone();
    private:
        Ant m_aAntArray[ANT_COUNT];
        Ant m_aBestAnt;
        double m_dbMaxPheromone;
        double m_dbMinPheromone;
        bool m_bIsFirstLoop;
};

#endif // NEWTSP_H
