#ifndef HELPER_H
#define HELPER_H

#include "Ant.h"

class Helper
{
    public:
        static int getRandom(const int&, int min = 0);
        static bool CheckPath(Ant);
};

#endif // HELPER_H
