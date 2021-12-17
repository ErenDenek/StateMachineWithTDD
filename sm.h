#ifndef SM_H
#define SM_H

#include <stdint.h>
/*
    todo:
    - State içinde entry, exit eventlerini çalışsın.
    - State eventleri kontrol etsin
    - State transition fonksiyonu olsun.
*/

/* DEFINITIONS */
#define EVT_ENTRY   ( -1 )
#define EVT_EXIT    ( -2 )
#define EVT_NONE    ( -3 )

#define CURR_STATE  ( self->state )
#define TAR_STATE   ( self->targetState )
#define CURR_EVENT  ( self->event )
#define TAR_EVENT   ( self->targetEvent )

typedef struct SM_TS SM_TS;
typedef void (*state_func_t)(SM_TS *const self);
typedef int32_t event_t;

/* STRUCTURES */
struct SM_TS{
    state_func_t state;

    state_func_t targetState;

    event_t event;

    event_t targetEvent;
};

/* FUNCTIONS */
void smInit( SM_TS *const self, state_func_t targetState );

void smSetEvent( SM_TS *const self, event_t event );

void smTransition( SM_TS *const self, state_func_t targetState );

void smStart( SM_TS *const self );

void smRun( SM_TS *const self );

#endif // SM_H
