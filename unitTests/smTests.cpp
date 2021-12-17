#include <CppUTest/TestHarness.h>

extern "C"
{
#include "stdio.h"
#include "sm.h"
}

SM_TS testSm;

enum TEST_EVENTS{
    EVT_MOTOR_RUN,
    EVT_ERROR,
    EVT_TIMEOUT,
    EVT_ESCAPE_ERROR
};

static void testTopState(SM_TS* const testSm);
static void testErrorState(SM_TS* const testSm);
static void testMotorRunState(SM_TS* const testSm);

TEST_GROUP(sm)
{
    void setup()
    {
        smInit(&testSm, &testTopState);
    }
    void teardown()
    {

    }
};

TEST(sm, smFirstTest)
{
    smRun(&testSm);
    smSetEvent(&testSm, EVT_MOTOR_RUN);
    smRun(&testSm);
    smSetEvent(&testSm, EVT_ERROR);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
    smSetEvent(&testSm, EVT_ESCAPE_ERROR);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
    smRun(&testSm);
}

static void testTopState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        //printf("Top State => Entry Event\n");
        break;
    case EVT_EXIT:
        //printf("Top State => Exit Event\n");
        break;
    case EVT_MOTOR_RUN:
        smTransition(testSm, testMotorRunState);
        //printf("Top State => MotorRun Event\n");
        break;
    }

    return;
}

static void testMotorRunState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        //printf("MotorRun State => Entry Event\n");
        break;
    case EVT_EXIT:
        //printf("MotorRun State => Exit Event\n");
        break;
    case EVT_ERROR:
        smTransition(testSm, testErrorState);
        //printf("MotorRun State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        //printf("MotorRun State => Timeout Event\n");
        break;
    }
}

static void testErrorState(SM_TS* const testSm)
{
    switch (testSm->event)
    {
    case EVT_ENTRY:
        //printf("Error State => Entry Event\n");
        break;
    case EVT_EXIT:
        //printf("Error State => Exit Event\n");
        break;

    case EVT_ESCAPE_ERROR:
        smTransition(testSm, testMotorRunState);
        //printf("Error State => Escape Error Event\n");
        break;
    }
    return;
}
