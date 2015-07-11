#include "NewTSP.h"
#include "parameter.h"
#include <iostream>
#include <fstream>
#include <time.h>
#include <stdlib.h>
#include <math.h>

using namespace std;


extern double g_Pheromone[CITY_COUNT][CITY_COUNT];
extern double g_Distance[CITY_COUNT][CITY_COUNT];
extern int g_nCenterCity;


/**
 *函数名：DistanceInit
 *功能：将文件内部的所有距离数据输入其中（默认）或者可以选择用户自己输入数据
 */
void NewTSP::DistanceInit()
{
    cout << "请输入所有的路径！\n" ;
//-----------------------读取文件夹的内容-----------------------
    fstream file;
	//测试数据输入路径：
    file.open("Test.tsp" , ios::in);
    for(int i = 0; i < CITY_COUNT; i++)
        for(int j = 0; j < CITY_COUNT; j++)
            file >> g_Distance[i][j];

    file.close();
//----------------------------------------------------------------

/*
-------------------------用户自己输入数据------------------------
    for(int i = 0 ; i < CITY_COUNT; i++)
        for(int j = 0; j < CITY_COUNT; j++)
            cin >> g_Distance[i][j];
-----------------------------------------------------------------
*/
    cout <<"数据获取完毕！\n" ;

    return ;
}



/**
 *函数名：InitData
 *功能：初始化信息，内容包括初始化全局最优蚂蚁、初始化地图距离、初始化地图信息素
 *函数中会调用上一个函数DistanceInit()来初始化地图数据
 */
void NewTSP::InitData()
{
    DistanceInit();

	m_aBestAnt.m_dbPathLength = INIT_BEST_ANT_MARK;
    //初始化信息素
    for(int i = 0; i < CITY_COUNT; i++)
        for(int j = 0; j < CITY_COUNT; j++)
            g_Pheromone[i][j] = PHEROMONE_ORIGINAL;

    m_bIsFirstLoop = true;
}


/**
 *函数名：TSPSearch
 *函数功能：进行TSP搜索，参数startPos表示设置的起点城市
 */
void NewTSP::TSPSearch()
{
	srand(time(NULL));

	//迭代，进行反复搜索
    for(int i = 0; i < ITERATIONS; i++)
    {
        //------------以下内容为每一次循环搜索----------------
        Ant iterate_best;
        iterate_best.m_dbPathLength = INIT_BEST_ANT_MARK;
		//对于该次的所有蚂蚁进行一次搜索
        for(int j = 0; j < ANT_COUNT; j++)
        {
            m_aAntArray[j].Search();
			//搜索完成以后比较看是否已经搜索到更好的线路
			if( m_aAntArray[j].ResultEvaluation() < iterate_best.ResultEvaluation() )
			{
				iterate_best = m_aAntArray[j];
			}

        }

        if(m_aBestAnt.ResultEvaluation() > iterate_best.ResultEvaluation() )
            m_aBestAnt = iterate_best;

		//---ForTest---
		cout << "ITERATOR:" << i << endl;
        for(int j = 0 ; j < PARALLEL_NUMBER; j++)
            cout << m_aBestAnt.m_dbSplitLength[j] <<"\t";
        cout <<endl << "结果评价得到" << m_aBestAnt.ResultEvaluation() << endl;
		//-------------


		UpdatePheromone();

        std::cin.get();


    }


    //输出最优路径情况：
	cout <<"结果最优路径为：";
	for(int i = 0 ; i < PATH_SIZE; i++)
		cout << " " << m_aBestAnt.m_nPath[i]  ;
}



/**
 *函数名：CalcMaxMinPheromone
 *功能：计算当前迭代情况下的信息素上限和下限
 *备注：对于原公式中f()改用了ResultEvaluation()函数的值来代替表示解的优越程度
 *另外原公式的分子也用Q来代替原来的1来增大最大最小信息素
 *其中avg的值可以针对不同情况进行修改
 */
bool NewTSP::CalcMaxMinPheromone()
{
    m_dbMaxPheromone = ENLARGE_PETERMITER_Q / ( (1 - ROU) * m_aBestAnt.ResultEvaluation() );
    double factor = pow(PBest, (double)(1.0 / CITY_COUNT) );
    int avg = (CITY_COUNT / 2) - 1;
    m_dbMinPheromone = (m_dbMaxPheromone*(1- factor)) / ((avg -1)*factor);
        cout <<"信息素最大值" << m_dbMaxPheromone <<"\t最小值：" << m_dbMinPheromone <<endl;
    if(m_dbMaxPheromone >= m_dbMinPheromone)
        return true;
    else
        return false;
}


/**
 *函数名：UpdatePheromone
 *功能：根据情况将地图上的信息素进行更新
 */
void NewTSP::UpdatePheromone()
{
    double dbTempAry[CITY_COUNT][CITY_COUNT];
    for(int i = 0; i < CITY_COUNT; i++)
        for(int j = 0; j < CITY_COUNT; j++)
            dbTempAry[i][j] = 0;

    int m = 0 ,
        n = 0;

    if(CalcMaxMinPheromone())
    {
        if(m_bIsFirstLoop)
        {
        //初次迭代，此时需要将所有的初始信息素值设定为信息素上限
            for(int i = 0;i < CITY_COUNT; i++)
                for(int j = 0; j < CITY_COUNT; j++)
                    g_Pheromone[i][j] = m_dbMaxPheromone;
            m_bIsFirstLoop = false;
        }
        else
        {
            for(int i = 0; i < ANT_COUNT; i++)  //每只蚂蚁留下的信息素
            {
                for(int j = 1; j < CITY_COUNT + PARALLEL_NUMBER; j++)     //每个城市之间的信息素
                {
                    m = m_aAntArray[i].m_nPath[j];
                    n = m_aAntArray[i].m_nPath[j-1];
                    dbTempAry[n][m] += ENLARGE_PETERMITER_Q / m_aAntArray[i].ResultEvaluation();
                    dbTempAry[m][n] = dbTempAry[n][m];
                }
            }

            //更新环境信息素
            for(int i = 0; i < CITY_COUNT; i++)
                for(int j = 0; j < CITY_COUNT; j++)
                {
                    g_Pheromone[i][j] = g_Pheromone[i][j] * ROU + dbTempAry[i][j];
                    if(g_Pheromone[i][j] >= m_dbMaxPheromone)
                        g_Pheromone[i][j] = m_dbMaxPheromone;
                    if(g_Pheromone[i][j] <= m_dbMinPheromone)
                        g_Pheromone[i][j] = m_dbMinPheromone;
                }
        }


    }
    else
        cout <<"信息素计算错误：最大信息素小于最小信息素" << endl;


}



