#ifndef HSM_H
#define HSM_H

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

#define STATE_CTOR(__parent__, __child__ )                  {&__parent__, &__child__},
#define HSM_INIT(__hsm__, __topState__, __stateSize__ )     hsmInit(&__hsm__, &__topState__, __stateSize__)
#define HSM_START(__hsm__)                                  hsmStart(&__hsm__)
#define HSM_RUN(__hsm__)                                    hsmRun(&__hsm__)
#define HSM_HANDLER(__state__)                              void __state__(HSM_TS* const _hsm)
#define HSM_TRANS(__targetState__)                          hsmTransition(_hsm, __targetState__)
#define HSM_SET_EVENT(__hsm__, __targetEvent__)             hsmSetEvent(__hsm__, __targetEvent__)
#define HSM_SET_EVENT_LOOP(__hsm__, __targetEventLoop__)    hsmSetEventLoop(__hsm__, __targetEventLoop__)

#define EVENT_GREATER_ZERO  (0)
/* TYPES */
typedef struct HSM_TS HSM_TS;
typedef void (*state_func_t)(HSM_TS *const self);
typedef int32_t event_t;

/* STRUCTURES */
struct HSM_TS{
    char const* stateName;

    uint32_t stateSize;

    state_func_t stateParent;

    state_func_t stateCurrent;

    state_func_t targetState;

    event_t event;

    event_t targetEvent;
};

/* FUNCTIONS */
void hsmInit( HSM_TS *const self, const state_func_t* stateTable, const uint32_t stateSize );

void hsmCtor( HSM_TS* const self, const state_func_t stateTable[][2], const char* const stateName );

void hsmSetEvent( HSM_TS* const self, const event_t event );

void hsmSetEventLoop( HSM_TS* const self, const event_t event );

void hsmTransition( HSM_TS* const self, const state_func_t targetState );

void hsmStart( HSM_TS* const self );

void hsmRun( HSM_TS* const self );
#endif // HSM_H
