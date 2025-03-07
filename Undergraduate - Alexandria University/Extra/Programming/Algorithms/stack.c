#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum {INT, CHAR, FLOAT, STRING} collection_type_t;


typedef char* str_t;

typedef struct stack_s {
    collection_type_t type;
    void* collection;
    size_t size;
    size_t top_index;
    bool resizeable;
} stack_t, *stack_p;

typedef struct stack_pool_s {
    stack_p* stacks;
    size_t size;
} stack_pool_t, *stack_pool_p;

stack_pool_t stack_pool = {NULL, 0};

stack_p new_stack(const collection_type_t type, const size_t upper_bound, const bool accept_resizing)
{
    stack_p s = NULL;
    s = malloc(sizeof(stack_t));
    if (s == NULL) return s;
    stack_pool.stacks = realloc(stack_pool.stacks, sizeof(stack_p) * (stack_pool.size+1));
    stack_pool.stacks[stack_pool.size] = s;
    stack_pool.size++;
    s->size = upper_bound;
    switch (type) {
        case INT:
            s->collection = malloc(sizeof(int) * upper_bound);
            s->resizeable = accept_resizing;
            s->top_index = 0;
            s->type = type;
            break;
        case CHAR:
            s->collection = malloc(sizeof(float) * upper_bound);
            s->resizeable = accept_resizing;
            s->top_index = 0;
            s->type = type;
            break;
        case STRING:
            s->collection = malloc(sizeof(str_t) * upper_bound);
            s->resizeable = accept_resizing;
            s->top_index = 0;
            s->type = type;
            break;
        case FLOAT:
            s->collection = malloc(sizeof(float) * upper_bound);
            s->resizeable = accept_resizing;
            s->top_index = 0;
            s->type = type;
            break;
    }
    return s;
}

void stack_push(stack_p s, void* elem)
{
    s->top_index++;
    switch (s->type) {
        case INT:
            *(((int*) s->collection) + s->top_index) = *((int*)elem);
            break;
        case CHAR:
            *((char*) s->collection + s->top_index) = *((char*)elem);
            break;
        case STRING:
            *((str_t*) s->collection + s->top_index) = malloc(sizeof(char) * strlen((str_t) elem));
            strcpy(*((str_t*) s->collection + s->top_index), (str_t) elem);
            break;
        case FLOAT:
            *((float*) s->collection + s->top_index) = *((float*)elem);
            break;
    }
}

void* stack_peek(stack_p s, size_t index)
{
    if (index > s->top_index) return NULL;
    switch (s->type) {
        case INT:
            return (int*) s->collection + index;
        case CHAR:
            return (char*) s->collection + index;
        case STRING:
            return (str_t*) s->collection + index;
        case FLOAT:
            return (float*) s->collection + index;
    }
}

void* stack_pop(stack_p s)
{
    if (s->top_index == 0) return NULL;
    switch (s->type) {
        case INT:
            return (int*) s->collection + s->top_index--;
        case CHAR:
            return (char*) s->collection + s->top_index--;
        case STRING:
            return (str_t*) s->collection + s->top_index--;
        case FLOAT:
            return (float*) s->collection + s->top_index--;
    }
}

inline bool stack_is_empty(stack_p s)
{
    return !s->top_index;
}

void free_stacks()
{
    size_t i;
    for (i = 0; i < stack_pool.size; ++i) {
        free(stack_pool.stacks[i]->collection);
        free(stack_pool.stacks[i]);
    }
}

int main()
{
    stack_p my_stack = new_stack(STRING, 10, false);
    int i;
    char* strlist[] = {"HELLO ", "world ", "my name is ", "youssef "};
    for (i = 0; i < 4; ++i) {
        stack_push(my_stack, strlist[i]);
    }
    while (!stack_is_empty(my_stack)) {
        printf("%s", *(str_t*)stack_pop(my_stack));
    }
    atexit(free_stacks);
    return 0;
}