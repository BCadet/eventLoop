#ifndef __EVENT_H
#define __EVENT_H
#pragma once

#include <stdint.h>

//typedef void (*fptr_t)(uint8_t,char*[]);
typedef void (*fptr_t)(void *);


struct event
{
    void * arg;
    fptr_t command;
};

#endif // __EVENT_H
