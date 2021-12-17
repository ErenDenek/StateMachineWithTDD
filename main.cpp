#include "globals.h"

extern "C"
{
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
}

#if RELEASE == 1

int main()
{
    printf("Deneme\n");

    return 0;
}


#elif UNIT_TEST == 1
#include "iostream"
#include <CppUTest/CommandLineTestRunner.h>

using namespace std;

int main(int ac, char** av)
{
    return CommandLineTestRunner::RunAllTests(ac, av);
}

#endif



