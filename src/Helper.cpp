#include "Helper.h"
#include "parameter.h"
#include "Ant.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

extern int g_nCenterCity;

int Helper::getRandom(const int& max, int min)
{
    return min + (rand() % (max-min)) ;
}

bool Helper::CheckPath(Ant ant)
{
    int count = PARALLEL_NUMBER;
    for(int i = 0; i < PATH_SIZE; i++)
    {
        if(ant.m_nPath[i] < 0)
        {
            cout <<"Ant构造路径异常！第"<< i <<"路径错误，全路径为：\n" ;
            for(int j = 0; j < PATH_SIZE; j++)
            {
                cout << ant.m_nPath[j] <<" ";
            }

            return false;
        }
        //检查并行情况
        if(ant.m_nPath[i] == g_nCenterCity)
            count --;
    }

    if(count == 0)
        return true;
    else
        return false;
}
