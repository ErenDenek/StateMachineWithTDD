#include "sm.h"

#define CURR_STATE  ( self->state )
#define TAR_STATE   ( self->targetState )
#define CURR_EVENT  ( self->event )
#define TAR_EVENT   ( self->targetEvent )

/* @function name   : smInit
 * @brief           : It sets the top state with topState parameter.
 *                  : It sets the target state, current event and target event with default parameters.
 *                  : It begins the exit event for the current state if there is a transition. Next state begins with entry event.
 * @params          : self => Reference of sm object.
 *                  : topState => This parameter determines top state.
 * @returns         : void
*/
void smInit(SM_TS *const self, const state_func_t topState )
{
    CURR_STATE = topState;

    TAR_STATE = CURR_STATE;

    CURR_EVENT = EVT_ENTRY; //First event must be entry event each state.

    TAR_EVENT = EVT_NONE;
}

/* @function name   : smStart
 * @brief           : It is begined handler of top state.
 * @params          : self => Reference of sm object.
 * @returns         : void
*/
void smStart( SM_TS *const self )
{
    if( CURR_STATE != NULL ) //Won't begin the handler If it doesn't set for any state handler.
    {
       CURR_STATE(self);
    }
}

/* @function name   : smRun
 * @brief           : It controls transition between states.
 *                  : It controls the events.
 *                  : It begins the exit event for the current state if there is a transition. Next state begins with entry event.
 * @params          : self => Reference of sm object.
 * @returns         : void
*/
void smRun( SM_TS *const self )
{
    static event_t lastEvent = EVT_ENTRY;

    if( CURR_EVENT != lastEvent || CURR_EVENT == EVT_LOOP ) //If there is a change on state of event.
    {
        lastEvent = CURR_EVENT; //lastEvent must be current event.

        if( CURR_STATE != NULL ) //Won't begin the handler If it doesn't set for any state handler.
        {
            CURR_STATE(self); //Run state( related function ) one times.
        }
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

/* @function name   : smTransition
 * @brief           : It sets target state with targetState parameter. Like this, can be transition between current state and target state.
 * @params          : self => Reference of sm object.
 *                  : targetState => Transition isn't successful If target state isn't state handler
 * @returns         : void
*/
void smTransition(SM_TS *const self, const state_func_t targetState )
{
    if( targetState != NULL )
    {
        TAR_STATE = targetState;
    }
}

/* @function name   : smSetEvent
 * @brief           : It dispatchs to related event of state.
 * @params          : self => Reference of sm object.
 *                  : event =>  event parameter set event of state.
 * @returns         : void
*/
void smSetEvent(SM_TS *const self, const event_t event )
{
        TAR_EVENT = event;
}



