#include "Ant.h"
#include "parameter.h"
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <float.h>

using std::cout;
using std::endl;

extern double g_Pheromone[CITY_COUNT][CITY_COUNT];
extern double g_Distance[CITY_COUNT][CITY_COUNT];
extern int g_nCenterCity;




void Ant::InitAnt()
{
    m_dbPathLength = 0;

    int i = 0;
    for(; i < CITY_COUNT; i++)
    {
        m_nAllowedCity[i] = 1;
        m_nPath[i] = -1;
    }
	for(; i < PATH_SIZE; i++)
        m_nPath[i] = -1;

    m_nMovedCityCount = 0;
    m_nAllowedCity[g_nCenterCity] = PARALLEL_NUMBER;
}

bool Ant::ChooseFirstCity()
{

    int city = Helper::getRandom(CITY_COUNT);

    if(city >=  CITY_COUNT || city < 0){
        std::cout << "ChooseFirstCity() error!\n选择的城市超出允许范围" << std::endl;
        return false;
    }

    //设置初始蚂蚁所在位置
    m_nCurCityNo = city;
    //将出发城市保存入路径数组中
    m_nPath[0] = m_nCurCityNo;
    -- m_nAllowedCity[m_nCurCityNo] ;
    m_nMovedCityCount = 1;

    return true;
}

void Ant::Move()
{
    int nCityNo = ChooseNextCity();

    //更新m_dbPathLength,当相邻城市一致时候惩罚
    if(m_nCurCityNo == nCityNo)
        m_dbPathLength += MAX_LENGTH;

    m_dbPathLength += g_Distance[m_nCurCityNo][nCityNo];
    //更新m_nPath
    m_nPath[m_nMovedCityCount] = nCityNo;
    //更新m_nAllowedCity
	-- m_nAllowedCity[nCityNo];
	//更新m_nCurCityNo;
    m_nCurCityNo = nCityNo;
    //更新m_nMovedCityCount;
    ++ m_nMovedCityCount;

}

bool Ant::Search()
{
    InitAnt();
    if( ChooseFirstCity() )
    {
        //构造路径，while循环结束后m_nPath已经形成
		while(m_nMovedCityCount < PATH_SIZE )
        {
            Move();
        }
        SplitPath();
        return true;
    }
    else
    {
        std::cout <<"Search() error!\nChooseFirstCity()返回错误结果" << std::endl;
        return false;
    }
}

//从startCity到endCity之间的信息素计算
double Ant::HeuristicFunction(int startCity, int endCity)
{
    //如果两个参数是同一座城市，则函数返回0表示不给予选择的机会；
    if(startCity == endCity)
        return 0.0;
    //如果终点城市是不允许选择的城市，也不给于选择的机会
    if( !m_nAllowedCity[endCity] )
        return 0.0;

    //信息素部分
    double pheromonePercent = pow(g_Pheromone[startCity][endCity] , ALPHA);
    double distancePercent = 1;

    if(g_Distance <= 0)
    {
        cout <<"heurishtic_function error!\n g_dbDistance[" <<startCity <<"][" << endCity<<"] = 0";
        return -1;
    }
    else
        distancePercent = pow(1 / g_Distance[startCity][endCity] , BETA);

    return pheromonePercent * distancePercent * ENLARGE_PETERMITER_Q;
}

//允许选择相邻的城市
int Ant::ChooseNextCity()
{
    int nSelectCity = -1;
    double dbPheromoneTotal = 0.0;
    double prob[CITY_COUNT];

    //计算当前城市到周围所有城市的信息素总和
    for(int i = 0; i < CITY_COUNT; i++)
    {
        if(m_nAllowedCity[i] >= 1)
        {
			//提高起点城市被选中的概率，避免在最后全部选中一个城市
			prob[i] = m_nAllowedCity[i] * HeuristicFunction(m_nCurCityNo,i);
            dbPheromoneTotal += prob[i];
        }
        else
            prob[i] = 0;
    }

    //===========================按照百分比进行轮盘选择===========================
    double dbTemp = 0.0;

    if(dbPheromoneTotal >= 0)
    {
        double number_between_zero_to_one = rand() / ( double(RAND_MAX)+1 );
        dbTemp = number_between_zero_to_one * dbPheromoneTotal;

        for(int i = 0; i < CITY_COUNT; i++)
        {
            if(m_nAllowedCity[i] >= 1)
            {
				dbTemp -= prob[i];
                if(dbTemp < 0.0)
                {
                    nSelectCity = i;
                    break;
                }
            }
        }

    }
    else
    {
        cout <<"ChooseNextCity() error!\ndbPheromoneTotal出现负数值！" <<endl;
        return -2;
    }

    //极端情况考虑：以上情况并未给出合理的nSelectCity
    if(nSelectCity == -1)
    {
        for(int i = 0; i < CITY_COUNT; i++)
        {
            if(m_nAllowedCity[i] >= 1 )
            {
                nSelectCity = i;
                break;
            }
        }
    }
    return nSelectCity;


}

void Ant::SplitPath()
{
    int startPos = 0;
    while(m_nPath[startPos] != g_nCenterCity)
        ++startPos;
    double length = 0;
    int lengthPartion = 0;
    int i = startPos;
    do
    {
        length += g_Distance[ m_nPath[i] ][ m_nPath[(i+1)% PATH_SIZE] ];
        if(m_nPath[(i+1)%PATH_SIZE ] == g_nCenterCity)
        {
            m_dbSplitLength[lengthPartion] = length;
            ++ lengthPartion;
            length = 0;
        }
        i = (i+1)%PATH_SIZE;
    }while(i != startPos);

}

double Ant::ResultEvaluation()
{

    if(m_dbPathLength == INIT_BEST_ANT_MARK)
        return MAX_LENGTH;
    for(int i = 0; i < PATH_SIZE; i++)
    {
        if(m_nPath[i] < 0)
        {
            cout <<"ResultEvaluation(),RESULT_ILLEGAL" << endl;
            cout <<"Print the Result:" ;
            for(int j = 0; j < PATH_SIZE; j++)
                cout << m_nPath[j] <<" ";
            cout << endl;
            return RESULT_ILLEGAL;
        }

    }


    double average_value = m_dbPathLength / PARALLEL_NUMBER;
    double variance_value = 0;


        //否则开始进行计算
    for(int i = 0; i < PARALLEL_NUMBER; i++)
    {
        variance_value += pow( (m_dbSplitLength[i] - average_value) ,2);
    }
	variance_value /= PARALLEL_NUMBER;
	variance_value = sqrt(variance_value);

	return average_value * AVERAGE_PERCENT + variance_value *(1- AVERAGE_PERCENT);
}

Ant& Ant::operator=(Ant &ant)
{
    if(this == &ant)
        return *this;

    m_dbPathLength = ant.m_dbPathLength;
    m_nCurCityNo = ant.m_nCurCityNo;
    m_nMovedCityCount = ant.m_nMovedCityCount;
    int i = 0;
    for(; i < CITY_COUNT; i++)
    {
            m_nPath[i] = ant.m_nPath[i];
            m_nAllowedCity[i] = ant.m_nAllowedCity[i];
    }

    for(; i < PATH_SIZE; i++)
        m_nPath[i] = ant.m_nPath[i];

    for(int j = 0; j < PARALLEL_NUMBER; j++)
        m_dbSplitLength[j] = ant.m_dbSplitLength[j];

    return *this;
}


//==============================检验函数================================
bool Ant::CheckPath(int startCity)
{
    int count = 0;
    for(int i = 0; i < CITY_COUNT + PARALLEL_NUMBER; i++)
    {

        if(m_nPath[i] < 0)
        {
            cout <<"出现路径错误：某一个城市未被选中！" << endl;
            //此处可输出城市经过情况！
            return false;
        }
        if(m_nPath[i] == startCity)
            ++count;
    }
    if(count != PARALLEL_NUMBER)
    {
        cout <<"路径中起点未走足够的次数！" << endl;
        return false;
    }
    return true;
}

void Ant::DisplayPath()
{
    cout <<"当前的蚂蚁路径为：";
    for(int i = 0; i < CITY_COUNT + PARALLEL_NUMBER; i++)
        cout <<m_nPath[i]<<" ";
}


