#ifndef ANT_H
#define ANT_H
#include "parameter.h"
#include "Helper.h"
extern const int CITY_COUNT ;
extern const int PARALLEL_NUMBER;

class Ant
{
    public:
        void InitAnt();
        bool ChooseFirstCity();    //选择第一个城市
        int ChooseNextCity();   //选择下一个城市

        void Move();        //选择一个城市进行一步移动
        bool Search();
        bool CreateCircle();
        void CalPathLength();
        double ResultEvaluation();
        double HeuristicFunction(int, int);
        void SplitPath();
        //-------------------------检验执行正常函数---------------------
        bool CheckPath(int);
        void DisplayPath();
        //--------------------------------------------------------------
        double m_dbPathLength;      //整个路径的长度
		double m_dbSplitLength[PARALLEL_NUMBER];    //分裂出来的每一段路径长度
		int m_nPath[ PATH_SIZE ]; //路径为城市数量和并行度（起始城市反复走的次数）

        //重载操作符：=
        Ant& operator= (Ant &);

    private:
        int m_nAllowedCity[CITY_COUNT];
        int m_nCurCityNo;
        int m_nMovedCityCount;



};

#endif // ANT_H
