#include "Helper.h"
#include "parameter.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

extern int g_nCenterCity;
extern double g_Distance[CITY_COUNT][CITY_COUNT];
extern double g_Pheromone[CITY_COUNT][CITY_COUNT];

int Helper::getRandom(const int& max, int min)
{
    return min + (rand() % (max-min)) ;
}


void Helper::CheckGlobePheronmone(){
    for(int i = 0; i < CITY_COUNT; i++){
        for(int j = 0; j < CITY_COUNT; j++){
            cout << g_Pheromone[i][j] <<" ";
        }
        cout << endl;
    }
}


bool Helper::CheckPath(int m_nPath[]) {
    int count = PARALLEL_NUMBER;
    for(int i = 0; i < PATH_SIZE; i++)
    {
        if(m_nPath[i] < 0)
        {
            cout <<"路径异常！第"<< i <<"路径错误，全路径为：\n" ;
            for(int j = 0; j < PATH_SIZE; j++)
            {
                cout << m_nPath[j] <<" ";
            }

            return false;
        }
        //检查并行情况
        if(m_nPath[i] == g_nCenterCity)
            count --;
    }

    if(count == 0)
        return true;
    else
        return false;
}


bool Helper::CheckResult(int path[])
{
    for(int i = 0; i < PATH_SIZE; i++){
        cout << path[i] <<"-->" << path[(i+1) % PATH_SIZE ]
        <<"\t:" <<  g_Distance[path[i]][path[(i+1)%PATH_SIZE]] << endl;
    }
    return true;
}

bool Helper::ParameterCheck()
{
    int CITY_COUNT_ENSURE = 1,
        ANT_COUNT_ENSURE = 2,
        ITERATIONS_ENSURE = 4,
        PARALLEL_NUMBER_ENSURE = 8,
        ERROR_AGAIN_TIMES_ENSURE = 16,
        BASIC_PARAMETER_ENSURE = 32,
        PHEROMONE_ORIGINAL_ENSURE = 64,
        AVERAGE_PERCENT_ENSURE = 128,
        SUCCESS = 255;

    int check = 0;
    if(CITY_COUNT > 0)
        check += CITY_COUNT_ENSURE;
    if(ANT_COUNT > 0)
        check += ANT_COUNT_ENSURE;
    if(ITERATIONS > 0)
        check += ITERATIONS_ENSURE;
    if(PARALLEL_NUMBER > 0)
        check += PARALLEL_NUMBER_ENSURE;
    if(ERROR_AGAIN_TIMES > 0)
        check += ERROR_AGAIN_TIMES_ENSURE;
    if(ALPHA > 0 && BETA > 0 && ROU > 0 && ROU <= 1)
        check += BASIC_PARAMETER_ENSURE;
    if(PHEROMONE_ORIGINAL > 0)
        check += PHEROMONE_ORIGINAL_ENSURE;
    if(AVERAGE_PERCENT >= 0 && AVERAGE_PERCENT <= 1)
        check += AVERAGE_PERCENT_ENSURE;

    if(check == SUCCESS)
    {
        cout <<"Parameter Valid!" << endl;
        return true;
    }

    else
    {
        cout <<"Error Code:" << SUCCESS - check << endl;
        return false;
    }
}

