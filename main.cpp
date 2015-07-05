#include<iostream>
#include "parameter.h"
#include "NewTSP.h"
using namespace std;



double g_Pheromone[CITY_COUNT][CITY_COUNT];
double g_Distance[CITY_COUNT][CITY_COUNT];



int main()
{
    NewTSP tsp;
    tsp.InitData();
    tsp.TSPSearch(2);

    return 0;
}
