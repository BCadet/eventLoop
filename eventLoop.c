#include "fifo.h"
#include "eventLoop.h"
#include "action.h"

eventLoop_state_t eventLoop_init(struct eventLoop *this)
{
    gll_init(&this->bindingList);
    this->eventsVector = 0;
    fifo_state_t state = fifo_init(&(this->actionFifo));
    return (eventLoop_state_t) state;
}

eventLoop_state_t eventLoop_add_event_bindings(struct eventLoop *this, struct event_binding *binding)
{
    binding->eventsLoopHandle = this;
    return gll_pushBack(&this->bindingList, binding);
}

static fifo_state_t execute_action(fifo_t *this)
{
    struct action *next_action = (struct action*) fifo_pop_one(this);

    if(next_action == NULL || next_action->command == NULL)
        return eventLoop_error;

    next_action->command(next_action->arg);
    return eventLoop_ok;
}

void test_binding(void *binding)
{
    struct event_binding *b = (struct event_binding*) binding;
    if(b->eventMatchPolicy == matchPolicyOR) // OR
    {
        if((b->eventsLoopHandle->eventsVector & b->eventMatchMask) != 0)
        {
            eventLoop_post_action(b->eventsLoopHandle, &b->action);
            b->eventsLoopHandle->eventsVector &= ~(b->eventsLoopHandle->eventsVector & b->eventMatchMask);
        }
    }
    else // AND
    {
        if((b->eventsLoopHandle->eventsVector & b->eventMatchMask) ==  b->eventMatchMask)
        {
            eventLoop_post_action(b->eventsLoopHandle, &b->action);
            b->eventsLoopHandle->eventsVector &= ~b->eventMatchMask;
        }
    }
    
}

static void handle_event(struct eventLoop *this)
{
    gll_each(&this->bindingList, test_binding);
}

eventLoop_state_t eventLoop_loop(struct eventLoop *this)
{
    handle_event(this);
    return execute_action(&this->actionFifo);
}

eventLoop_state_t eventLoop_post_action(struct eventLoop *this, struct action *action)
{
    fifo_state_t state = fifo_push_one(&(this->actionFifo), action);
    return (eventLoop_state_t) state;
}

eventLoop_state_t eventLoop_trigger_event(struct eventLoop *this, uint8_t event)
{
    this->eventsVector |= (1<<event);
}