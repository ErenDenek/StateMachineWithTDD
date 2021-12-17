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

/* Event of states. It is optionally. */
enum TEST_EVENTS{
    EVT_MOTOR_RUN,
    EVT_ERROR,
    EVT_TIMEOUT,
    EVT_ESCAPE_ERROR
};

/* Functions protypes */
SM_HANDLER(topState);
SM_HANDLER(ErrorState);
SM_HANDLER(MotorRunState);
SM_HANDLER(MotorStopState);

int main()
{

    /* State-machine is initialized */
    SM_INIT(motorControlSm, topState);

    /* State-machine is started */
    SM_START(motorControlSm);

    for(int i = 0; i < 1000; i++)
    {
        SM_RUN(motorControlSm);

        if( i % 10 == 0 ) // Assume that it is triggered in 10 ms.
        {
            SM_SET_EVENT( &motorControlSm, EVT_TIMEOUT);
        }

    }


    for( int i = 0; i < 1000; i++ )
    {
        SM_RUN(motorControlSm);

        if( i == 100 ){
            SM_SET_EVENT( &motorControlSm, EVT_ERROR );
        }
        else if( i == 950 ){
            SM_SET_EVENT( &motorControlSm, EVT_ESCAPE_ERROR );
        }
    }

    return 0;
}

SM_HANDLER(topState)
{
    switch (_sm->event)
    {
    case EVT_ENTRY:
        SM_SET_EVENT(_sm, EVT_MOTOR_RUN);
        printf("Top State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Top State => Exit Event\n");
        break;
    case EVT_MOTOR_RUN:
        SM_TRANS(MotorRunState);
        printf("Top State => MotorRun Event\n");
        break;
    }

    return;
}

SM_HANDLER(ErrorState)
{
    switch (_sm->event)
    {
    case EVT_ENTRY:
        printf("Error State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Error State => Exit Event\n");
        break;

    case EVT_ESCAPE_ERROR:
        SM_TRANS(MotorStopState);
        printf("Error State => Escape Error Event\n");
        break;
    }

    return;
}

SM_HANDLER(MotorRunState)
{
    switch (_sm->event)
    {
    case EVT_ENTRY:
        printf("MotorRun State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorRun State => Exit Event\n");
        break;
    case EVT_ERROR:
        SM_TRANS(ErrorState);
        printf("MotorRun State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        SM_TRANS(MotorStopState);
        printf("MotorRun State => Timeout Event\n");
        break;
    }

    return;
}

SM_HANDLER(MotorStopState)
{
    switch (_sm->event)
    {
    case EVT_ENTRY:
        printf("MotorStop State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorStop State => Exit Event\n");
        break;
    case EVT_ERROR:
        SM_TRANS(ErrorState);
        printf("MotorStop State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        SM_TRANS(MotorRunState);
        printf("MotorStop State => Timeout Event\n");
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



