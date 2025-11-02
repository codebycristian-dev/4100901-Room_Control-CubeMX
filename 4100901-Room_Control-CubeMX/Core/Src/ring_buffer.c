#include "ring_buffer.h"

void ring_buffer_init(ring_buffer_t *rb, uint8_t *buffer, uint16_t capacity)
{
    rb->buffer = buffer;
    rb->capacity = capacity;
    ring_buffer_flush(rb); // Reutilizamos flush para inicializar head y tail
}

bool ring_buffer_write(ring_buffer_t *rb, uint8_t data)
{
    uint16_t next_head = (rb->head + 1) % rb->capacity;
    if (ring_buffer_is_full(rb)) // Usamos is_full en lugar de comparar directamente
    {
        rb->tail = (rb->tail + 1) % rb->capacity;
    }

    rb->buffer[rb->head] = data;
    rb->head = next_head;
    return true;
}

bool ring_buffer_read(ring_buffer_t *rb, uint8_t *data)
{
    if (ring_buffer_is_empty(rb)) // Usamos is_empty en lugar de comparar directamente
    {
        return false;
    }
    *data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % rb->capacity;
    return true;
}

uint16_t ring_buffer_count(ring_buffer_t *rb)
{
    if (rb->head >= rb->tail)
    {
        return rb->head - rb->tail;
    }
    return rb->capacity - (rb->tail - rb->head);
}

bool ring_buffer_is_empty(ring_buffer_t *rb)
{
    return rb->head == rb->tail;
}

bool ring_buffer_is_full(ring_buffer_t *rb)
{
    return ((rb->head + 1) % rb->capacity) == rb->tail;
}

void ring_buffer_flush(ring_buffer_t *rb)
{
    rb->head = rb->tail = 0;
}