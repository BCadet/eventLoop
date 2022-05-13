#include "fifo_event.h"
#include "eventLoop.h"

enum eventLoop_status eventLoop_init(struct eventLoop *eventLoop)
{
    enum fifo_event_state status = fifo_event_init(&(eventLoop->eventFifo));
    return (enum eventLoop_status) status;
}

enum eventLoop_status eventLoop_loop(struct eventLoop *eventLoop)
{
    struct event next_event;
    enum fifo_event_state status = fifo_event_pop_one(&(eventLoop->eventFifo), &next_event);
    if(status == fifo_event_ok && next_event.command != NULL)
    {
        next_event.command(next_event.arg);
    }
    return (enum eventLoop_status) status;
}

enum eventLoop_status eventLoop_post_event(struct eventLoop *eventLoop, struct event *event)
{
    enum fifo_event_state status = fifo_event_push_one(&(eventLoop->eventFifo), *event);
    return (enum eventLoop_status) status;
}