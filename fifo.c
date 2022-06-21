#include "fifo.h"


fifo_state_t fifo_init(fifo_t *fifo)
{
    fifo = gll_init(fifo);
    return  fifo_ok;
}

fifo_state_t fifo_push_one(fifo_t *fifo, void *element)
{
    if(gll_pushBack(fifo, element) != 0)
        return fifo_ko;

    return fifo_ok;
}

void* fifo_pop_one(fifo_t *fifo)
{
    return gll_pop(fifo);
}

fifo_state_t fifo_push(fifo_t *fifo, void *elementTable, size_t elementSize, uint8_t number_of_elements)
{
    int ret = 0;
    for(uint8_t i=0; ret == 0 && i<number_of_elements; i++)
    {
        ret = fifo_push_one(fifo, elementTable + i*elementSize);
    }

    if(ret != 0)
        return fifo_ko;

    return fifo_ok;
}

//faut tester ça !
fifo_state_t fifo_pop(fifo_t *fifo, void *elementTable, size_t elementSize, uint8_t number_of_elements)
{
    if(fifo->size < number_of_elements)
        return fifo_ko;

    for(uint8_t i=0; i< number_of_elements; i++)
    {
        void *element = elementTable + i*elementSize;
        element = fifo_pop_one(fifo);
        if(element == NULL)
            return fifo_ko;
    }

    return fifo_ok;
}