#include "globals.h"

extern "C"
{
    #include <stdio.h>
    #include <stdint.h>
    #include <stdbool.h>
    #include "sm.h"
}

#if RELEASE == 1

SM_TS motorControlSm;

static void testTopState(SM_TS* const testSm);
static void testErrorState(SM_TS* const testSm);
static void testMotorRunState(SM_TS* const testSm);
static void testMotorStopState(SM_TS* const testSm);

enum TEST_EVENTS{
    EVT_MOTOR_RUN,
    EVT_ERROR,
    EVT_TIMEOUT,
    EVT_ESCAPE_ERROR
};


int main()
{
    smInit(&motorControlSm, &testTopState);

    smStart(&motorControlSm);
    smSetEvent(&motorControlSm, EVT_MOTOR_RUN);

    for(int i = 0; i < 50; i++)
    {
        smRun(&motorControlSm);
        smSetEvent(&motorControlSm, EVT_TIMEOUT);
    }

    return 0;
}

static void testTopState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        printf("Top State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Top State => Exit Event\n");
        break;
    case EVT_MOTOR_RUN:
        smTransition(testSm, testMotorRunState);
        printf("Top State => MotorRun Event\n");
        break;
    }

    return;
}

static void testMotorRunState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        printf("MotorRun State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorRun State => Exit Event\n");
        break;
    case EVT_ERROR:
        smTransition(testSm, testMotorRunState);
        printf("MotorRun State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        smTransition(testSm, testMotorStopState);
        printf("MotorRun State => Timeout Event\n");
        break;
    }

    return;
}

static void testMotorStopState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        printf("MotorStop State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorStop State => Exit Event\n");
        break;
    case EVT_ERROR:
        smTransition(testSm, testErrorState);
        printf("MotorStop State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        smTransition(testSm, testMotorRunState);
        printf("MotorStop State => Timeout Event\n");
        break;
    }

    return;
}

static void testErrorState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        printf("Error State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Error State => Exit Event\n");
        break;

    case EVT_ESCAPE_ERROR:
        smTransition(testSm, testMotorRunState);
        printf("Error State => Escape Error Event\n");
        break;
    }

    return;
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



