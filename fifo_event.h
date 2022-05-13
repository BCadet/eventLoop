#ifndef __FIFO_event_H
#define __FIFO_event_H
#pragma once

//
#include "event.h"
// std
#include <stdint.h>
#include <stdlib.h>

//! Available state for fifo module
    enum fifo_event_state
    {
        fifo_event_ok = 0,
        fifo_event_empty = 1,
        fifo_event_full = 2
    };

//! \brief Data to manage a fifo
//!
struct fifo_event
{
    //! buffer pointer
	struct event buffer[40];
    //! buffer size
    uint32_t capacity;
    //! Index of the next element that must be read
    uint32_t read;
    //! Index of the next element 
    uint32_t write;
    //! Internal management
    uint8_t overlap_flag;
};

//! \brief Constructor
//!
enum fifo_event_state fifo_event_init(struct fifo_event* _this);

//! \brief To get the state of the fifo (empty, full else ok)
//!
enum fifo_event_state fifo_event_state(struct fifo_event* _this);

//! \brief To append n elements to the fifo
//!
//! \return The number of elements successfuly stored in the fifo. If not equel to size the fifo is probably full
//!
size_t fifo_event_push(struct fifo_event* _this, const struct event* element_buffer, size_t size);

//! \brief To append an element to the fifo
//!
enum fifo_event_state fifo_event_push_one(struct fifo_event* _this, struct event element);

//! \brief Get n elements of the fifo, elements are removed
//!
size_t fifo_event_pop(struct fifo_event* _this, struct event* element_buffer, size_t size);

//! \brief Get an element of the fifo, the element is removed
//!
enum fifo_event_state fifo_event_pop_one(struct fifo_event* _this, struct event* element);

//! \brief Clear data fifo
//!
enum fifo_event_state fifo_event_clear(struct fifo_event* _this);

//! \brief Return the number of element stored in the fifo
//!
size_t fifo_event_size(struct fifo_event* _this);

//! \brief Return the number of element left that can be stored
//!
static inline size_t fifo_event_capacity_left(struct fifo_event* _this) { return _this->capacity - fifo_event_size(_this); }

#endif // __FIFO_event_H
