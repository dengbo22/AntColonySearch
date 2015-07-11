#include "Helper.h"
#include "parameter.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int Helper::getRandom(const int& max, int min)
{
    return min + (rand() % (max-min)) ;
}
