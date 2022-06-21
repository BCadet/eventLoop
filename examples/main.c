#include "eventLoop.h"
#include <stdio.h>

struct eventLoop event_loop;
struct event_binding bindings[3];

void event_handler(void *args)
{
    int event = (int)args;

    printf("event_handler: %d\n", event);
    printf("bindings[%d].eventMatchMask = 0x%X\n", event, bindings[event].eventMatchMask);
    printf("bindings[%d].eventMatchPolicy = %d\n", event, bindings[event].eventMatchPolicy);
    printf("event_loop.eventsVector = 0x%X\n", event_loop.eventsVector);

    switch (event)
    {
    default:
    case 0:
        eventLoop_trigger_event(&event_loop, 1);
        eventLoop_trigger_event(&event_loop, 2);
        break;
    case 1:
        eventLoop_trigger_event(&event_loop, 3);
        break;
    case 2:
        eventLoop_trigger_event(&event_loop, 0);
        break;
    }
}

int main()
{
    bindings[0].action.command = event_handler;
    bindings[0].action.arg = (void *)0;
    bindings[0].eventMatchMask = (1 << 0);
    bindings[0].eventMatchPolicy = matchPolicyOR;

    bindings[1].action.command = event_handler;
    bindings[1].action.arg = (void *)1;
    bindings[1].eventMatchMask = (1 << 1);
    bindings[1].eventMatchPolicy = matchPolicyOR;

    bindings[2].action.command = event_handler;
    bindings[2].action.arg = (void *)2;
    bindings[2].eventMatchMask = (1 << 2) | (1 << 3);
    bindings[2].eventMatchPolicy = matchPolicyAND;

    printf("eventLoop init\n");
    eventLoop_init(&event_loop);
    eventLoop_add_event_bindings(&event_loop, &bindings[0]);
    eventLoop_add_event_bindings(&event_loop, &bindings[1]);
    eventLoop_add_event_bindings(&event_loop, &bindings[2]);
    printf("eventLoop trigger event 0\n");
    eventLoop_trigger_event(&event_loop, 0);

    while (1)
    {
        eventLoop_loop(&event_loop);
        sleep(1);
    }
}