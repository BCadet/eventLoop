#ifndef __EVENTLOOP_H
#define __EVENTLOOP_H
#pragma once

#include "fifo_event.h"
#include <stdio.h>
#include <stdlib.h>

struct eventLoop
{
    struct fifo_event eventFifo;
};

enum eventLoop_status
{
    EventLoop_OK = 0,
    EventLoop_EMPTY = 1,
    EventLoop_FULL = 2
};

enum eventLoop_status eventLoop_init(struct eventLoop *eventLoop);
enum eventLoop_status eventLoop_loop(struct eventLoop *eventLoop);
enum eventLoop_status eventLoop_post_event(struct eventLoop *eventLoop, struct event *event);

#endif // __ACTION_LOOP_H
