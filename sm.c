#include "sm.h"

void smInit( SM_TS *const self, state_func_t topState )
{
    CURR_STATE = topState;

    TAR_STATE = CURR_STATE;

    CURR_EVENT = EVT_ENTRY; //First event must be entry event each state.

    TAR_EVENT = EVT_NONE;
}

void smStart( SM_TS *const self )
{
    if( CURR_STATE != NULL )
    {
       CURR_STATE(self);
    }
}

void smRun( SM_TS *const self )
{
    static event_t lastEvent = EVT_ENTRY;

    if( CURR_EVENT != lastEvent ) //If there is a change on state of event.
    {
        lastEvent = CURR_EVENT; //lastEvent must be current event.
        CURR_STATE(self); //Run state( related function ) one times.
    }

    if( CURR_STATE != TAR_STATE ) //While exiting from state, exit event is processed If there is a transition among any state. After, current event is setted as entry event for target state.
    {
        static uint8_t sta = 0;

        if( sta == 0 ){
            CURR_EVENT = EVT_EXIT;
            sta = 1;
        }else{
            CURR_STATE = TAR_STATE;
            CURR_EVENT = EVT_ENTRY;
            sta = 0;
        }
    }
    else //Target event can process If there is no a transition among any states.
    {
        CURR_EVENT = TAR_EVENT;
    }
}

void smTransition( SM_TS *const self, state_func_t targetState )
{
    TAR_STATE = targetState;
}

void smSetEvent( SM_TS *const self, event_t event )
{
    TAR_EVENT = event;
}



