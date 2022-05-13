// fifo
#include "fifo_event.h"

// std
#include <string.h>

// ============================================================================
//

enum fifo_event_state fifo_event_init(struct fifo_event *_this)
{
    _this->capacity = 40;
    _this->read = 0;
    _this->write = 0;
    _this->overlap_flag = 0;
    return fifo_event_ok;
}

// ============================================================================
//

enum fifo_event_state fifo_event_state(struct fifo_event *_this)
{
    if ((_this->read == _this->write) && _this->overlap_flag)
    {
        return fifo_event_full;
    }
    else if ((_this->read == _this->write) && !_this->overlap_flag)
    {
        return fifo_event_empty;
    }
    else
    {
        return fifo_event_ok;
    }
}

// ============================================================================
//

size_t fifo_event_push(struct fifo_event *_this, const struct event *element_buffer, size_t size)
{
    uint32_t capacity_left = fifo_event_capacity_left(_this);

    // Check if there is enough space left in the fifo
    // If not copy only the number of element that fit the remaining space
    if (capacity_left < size)
    {
        size = capacity_left;
    }

    //
    if ((_this->write + size) >= _this->capacity)
    {
        // Need 2 memcpy

        // Compute overflow
        size_t overflow = (_this->write + size) - _this->capacity;
        size_t size_tmp = size - overflow;

        // current write to end of buffer
        memcpy((_this->buffer + _this->write), element_buffer, size_tmp * sizeof(struct event));

        // start of buffer to final index
        memcpy(_this->buffer, element_buffer + size_tmp, overflow * sizeof(struct event));
        _this->overlap_flag = 1;
    }
    else
    {
        // Easy case
        memcpy((_this->buffer + _this->write), element_buffer, size * sizeof(struct event));
    }
    _this->write = (_this->write + size) % _this->capacity;
    return size;
}

// ============================================================================
//

enum fifo_event_state fifo_event_push_one(struct fifo_event *_this, struct event element)
{
    if (fifo_event_state(_this) == fifo_event_full)
    {
        return fifo_event_full;
    }

    memcpy(&(_this->buffer[_this->write]), &(element),
       sizeof(struct event));

    if (_this->capacity == _this->write + 1)
    {
        _this->overlap_flag = 1;
    }
    _this->write = (_this->write + 1) % _this->capacity;
    return fifo_event_ok;
}

// ============================================================================
//

size_t fifo_event_pop(struct fifo_event *_this, struct event *element_buffer, size_t size)
{
    uint32_t capacity = fifo_event_size(_this);

    // If the size specified by the user is greater then the size of the available
    // data in the fifo, the output will be the size of the available data
    if (capacity < size)
    {
        size = capacity;
    }

    //
    if ((_this->read + size) >= _this->capacity)
    {
        // Need 2 memcpy

        // Compute overflow
        size_t overflow = (_this->read + size) - _this->capacity;
        size_t size_tmp = size - overflow;

        // current read to end of the fifo
        memcpy(element_buffer, (_this->buffer + _this->read), size_tmp * sizeof(struct event));

        // start of the fifo to final index
        memcpy(element_buffer + size_tmp, _this->buffer, overflow * sizeof(struct event));
        _this->overlap_flag = 0;
    }
    else
    {
        // Easy case
        memcpy(element_buffer, (_this->buffer + _this->read), size * sizeof(struct event));
    }
    _this->read = (_this->read + size) % _this->capacity;
    return size;
}

// ============================================================================
//

enum fifo_event_state fifo_event_pop_one(struct fifo_event *_this, struct event *element)
{
    if (fifo_event_state(_this) == fifo_event_empty)
    {
        return fifo_event_empty;
    }

    memcpy((element), &(_this->buffer[_this->read]),
       sizeof(struct event));

    if (_this->capacity == _this->read + 1)
    {
        _this->overlap_flag = 0;
    }

    _this->read = (_this->read + 1) % _this->capacity;
    return fifo_event_ok;
}

// ============================================================================
//

enum fifo_event_state fifo_event_clear(struct fifo_event *_this)
{
    _this->read = 0;
    _this->write = 0;
    _this->overlap_flag = 0;
    return fifo_event_ok;
}

// ============================================================================
//
size_t fifo_event_size(struct fifo_event *_this)
{
    switch (fifo_event_state(_this))
    {
    case fifo_event_full:
        return _this->capacity;

    case fifo_event_empty:
        return 0;

    default:
    {
        size_t size = 0;
        // Suppose that write always != read because not empty and not full here
        if (_this->write > _this->read)
        {
            size = _this->write - _this->read;
        }
        else
        {
            // \todo potentiel bug if the fifo has a capacity too big ( max value of (size_t) / 2 )
            size = (_this->write + _this->capacity) - _this->read;
        }
        return size;
    }
    }
}
