#ifndef __ACTION_H
#define __ACTION_H
#pragma once

#include <stdint.h>

//typedef void (*fptr_t)(uint8_t,char*[]);
typedef void (*fptr_t)(void *);


struct action
{
    void * arg;
    fptr_t command;
};

#endif // __ACTION_H
