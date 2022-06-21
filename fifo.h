#ifndef FIFO_H
#define FIFO_H
#pragma once

#include "gll.h"

typedef gll_t fifo_t;

typedef enum
{
    fifo_ok,
    fifo_ko,
} fifo_state_t;

fifo_state_t fifo_init(fifo_t *fifo);
fifo_state_t fifo_push_one(fifo_t *fifo, void *element);
void* fifo_pop_one(fifo_t *fifo);
fifo_state_t fifo_push(fifo_t *fifo, void *elementTable, size_t elementSize, uint8_t number_of_elements);
fifo_state_t fifo_pop(fifo_t *fifo, void *elementTable, size_t elementSize, uint8_t number_of_elements);

#endif