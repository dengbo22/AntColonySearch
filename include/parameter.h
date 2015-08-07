#ifndef PARAMETER_H_INCLUDED
#define PARAMETER_H_INCLUDED


//Instance Parameter
const int CITY_COUNT = 52;
const int ANT_COUNT = 34;
const int ITERATIONS = 1000;
const int PARALLEL_NUMBER = 1;
const double MAX_LENGTH = 100000000;
const int ERROR_AGAIN_TIMES = 5;


//Ant Colony Optimization Parameter
const double ALPHA = 2.0;
const double BETA = 2.0;
const double ROU = 0.9;
const double PHEROMONE_ORIGINAL = 1.0;
const double AVERAGE_PERCENT = 1;
const double PBest = 0.5;
const double ENLARGE_PETERMITER_Q = 1000;

const double INIT_BEST_ANT_MARK = -1 ;




#define     PATH_SIZE           (CITY_COUNT + PARALLEL_NUMBER - 1)
#define     RESULT_ILLEGAL      MAX_LENGTH




#endif // PARAMETER_H_INCLUDED
