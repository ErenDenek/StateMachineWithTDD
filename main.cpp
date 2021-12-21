#include "globals.h"

extern "C"
{
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "hsm/hsm.h"
}

#if RELEASE == 1

HSM_TS motorControlSm;

/* Event of states. It is optionally. */
enum TEST_EVENTS{
    EVT_MOTOR_RUN,
    EVT_ERROR,
    EVT_TIMEOUT,
    EVT_ESCAPE_ERROR,
    EVT_LOOP
};

/* State Handler prototypes */
HSM_HANDLER(stop);
HSM_HANDLER(s1);
HSM_HANDLER(s2);
HSM_HANDLER(s3);

static const state_func_t states[][2] =
{
    STATE_CTOR(stop, s1)
    STATE_CTOR(s1, s2)
    STATE_CTOR(s2, s3)
};

int main()
{
    //HSM_INIT(motorControlSm, states[0][0], sizeof(states)/sizeof(states[0]));
    hsmInit(&motorControlSm, &states[0][0], sizeof(states)/sizeof(states[0]) );
    HSM_START(motorControlSm);

    for(int i = 0; i < 100; i++ )
    {
        HSM_RUN(motorControlSm);

        printf("%d. ", i);
        if( i == 20 )
        {
            HSM_SET_EVENT( &motorControlSm, EVT_ERROR );
        }
    }

    return 0;
}

HSM_HANDLER(stop)
{
    switch (_hsm->event)
    {
    case EVT_ENTRY:
        HSM_SET_EVENT(_hsm, EVT_MOTOR_RUN);
        printf("Top State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Top State => Exit Event\n");
        break;
    case EVT_MOTOR_RUN:
        printf("Top State => MotorRun Event\n");
        break;
    }

    return;
}

HSM_HANDLER(s1)
{
    switch (_hsm->event)
    {
    case EVT_ENTRY:
        printf("Error State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("Error State => Exit Event\n");
        break;
    case EVT_ESCAPE_ERROR:
        printf("Error State => Escape Error Event\n");
        break;
    }

    return;
}

HSM_HANDLER(s2)
{
    switch (_hsm->event)
    {
    case EVT_ENTRY:
        HSM_SET_EVENT_LOOP(_hsm, EVT_LOOP);
        printf("MotorRun State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorRun State => Exit Event\n");
        break;
    case EVT_LOOP:
        printf("MotorRun State => Loop Event\n");
        break;
    case EVT_ERROR:
        printf("MotorRun State => Error Event\n");
        break;
    case EVT_TIMEOUT:
        printf("MotorRun State => Timeout Event\n");
        break;
    }

    return;
}

HSM_HANDLER(s3)
{
    switch (_hsm->event)
    {
    case EVT_ENTRY:
        printf("MotorStop State => Entry Event\n");
        break;
    case EVT_EXIT:
        printf("MotorStop State => Exit Event\n");
        break;
    case EVT_ERROR:
        printf("MotorStop State => Error Event\n");
        break;
    case EVT_TIMEOUT:
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



