#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "Helper.h"
#include "parameter.h"
#include "NewTSP.h"
using namespace std;



double g_Pheromone[CITY_COUNT][CITY_COUNT];
double g_Distance[CITY_COUNT][CITY_COUNT];
int g_nCenterCity = 0;


int main()
{

    if(Helper::ParameterCheck())
    {
        srand(time(NULL));
        NewTSP tsp;
        tsp.InitData();
        tsp.TSPSearch();
    }
    else
        std::cin.get();


    return 0;
}
