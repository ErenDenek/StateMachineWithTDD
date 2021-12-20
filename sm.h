#ifndef SM_H
#define SM_H

#include <stdint.h>
/*
    todo:
    - Takip edilebilirlik için hangi state ve event üzerinde olduğu kaydedebiliriz.
    - Debug için sm history fonksiyonları yazılabilir.
    - Ctor fonksiyonu eklenebilir.
*/

/* DEFINITIONS */
#define EVT_ENTRY   ( -1 )
#define EVT_EXIT    ( -2 )
#define EVT_NONE    ( -3 )
#define EVT_LOOP    ( -4 )

#define SM_INIT(__sm__, __topState__)           smInit(&__sm__, &__topState__)
#define SM_START(__sm__)                        smStart(&__sm__)
#define SM_RUN(__sm__)                          smRun(&__sm__)
#define SM_HANDLER(__state__)                   void __state__(SM_TS* const _sm)
#define SM_TRANS(__targetState__)               smTransition(_sm, __targetState__)
#define SM_SET_EVENT(__sm__, __targetEvent__)   smSetEvent(__sm__, __targetEvent__)

#define EVENT_GREATER_ZERO  (0)
/* TYPES */
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
void smInit( SM_TS *const self, const state_func_t topState );

void smSetEvent( SM_TS *const self, const event_t event );

void smTransition( SM_TS *const self, const state_func_t targetState );

void smStart( SM_TS *const self );

void smRun( SM_TS *const self );

#endif // SM_H
