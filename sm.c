#include "sm.h"

#define CURR_STATE  ( self->state )
#define TAR_STATE   ( self->targetState )
#define CURR_EVENT  ( self->event )

void smInit( SM_TS *const self, state_func_t topState )
{
    CURR_STATE = topState;

    TAR_STATE = CURR_STATE;

    CURR_EVENT = EVT_ENTRY; //First event must be entry event each state.
}

void smRun( SM_TS *const self )
{
    static event_t lastEvent;

    if( CURR_EVENT != lastEvent ) //If there is a change on state of event.
    {
        lastEvent = CURR_EVENT; //lastEvent must be current event.
        CURR_STATE(self); //Run state( related function ) one times.
    }

    if( CURR_STATE != TAR_STATE )
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
}

void smTransition( SM_TS *const self, state_func_t targetState )
{
    TAR_STATE = targetState;
}

void smSetEvent( SM_TS *const self, event_t event )
{
    CURR_EVENT = event;
}



