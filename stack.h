#pragma once

#include <cstdio>
#include <cstdlib>
#include <stddef.h>

typedef struct stack
{
    size_t capacity; 
    size_t current_size;
    size_t elem_size;
    void* data;
}Stack;

struct stack* stack_new(size_t elem_size);
int stack_push(struct stack *st, const void *elem);
int stack_pop (struct stack *st, void *elem);