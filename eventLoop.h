#ifndef __EVENTLOOP_H
#define __EVENTLOOP_H
#pragma once

#include "fifo.h"
#include <stdio.h>
#include <stdlib.h>
#include "gll.h"
#include "action.h"

struct eventLoop
{
    uint32_t eventsVector;
    gll_t bindingList;
    fifo_t actionFifo;
};

typedef enum
{
    matchPolicyAND,
    matchPolicyOR,
} matchPolicy_t;

struct event_binding
{
    struct eventLoop *eventsLoopHandle;
    struct action action;
    uint32_t eventMatchMask;
    matchPolicy_t eventMatchPolicy;

};

typedef enum 
{
    eventLoop_ok,
    eventLoop_error,
    eventLoop_empty,
    enventLoop_full,
} eventLoop_state_t;

eventLoop_state_t eventLoop_init(struct eventLoop *this);
eventLoop_state_t eventLoop_add_event_bindings(struct eventLoop *this, struct event_binding *binding);
eventLoop_state_t eventLoop_loop(struct eventLoop *this);
eventLoop_state_t eventLoop_post_action(struct eventLoop *this, struct action *action);
eventLoop_state_t eventLoop_trigger_event(struct eventLoop *this, uint8_t event);
#endif // __ACTION_LOOP_H
