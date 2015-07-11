#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "parameter.h"
#include "NewTSP.h"
using namespace std;



double g_Pheromone[CITY_COUNT][CITY_COUNT];
double g_Distance[CITY_COUNT][CITY_COUNT];
int g_nCenterCity = 0;


int main()
{
    srand(time(NULL));
    NewTSP tsp;
    tsp.InitData();
    tsp.TSPSearch();

    return 0;
}
