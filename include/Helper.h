#ifndef HELPER_H
#define HELPER_H
#include <fstream>

class Helper
{
    public:
        static int getRandom(const int&, int min = 0);
        static void CheckGlobePheronmone();
        static bool CheckPath(int[]);
        static bool CheckResult(int[]);
        static bool ParameterCheck();

};

#endif // HELPER_H
