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
static void testMotorStopState(SM_TS* const testSm);

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
    smStart(&testSm);
    smSetEvent(&testSm, EVT_MOTOR_RUN);

    for(int i = 0; i < 52; i++ )
    {
        smRun(&testSm);
    }
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
        smSetEvent(testSm, EVT_TIMEOUT);
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
        smSetEvent(testSm, EVT_TIMEOUT);
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


