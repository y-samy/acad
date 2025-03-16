/*
 * Assignment on int queues and stacks, no other datatypes will be implemented
 * Contiguous collection representation (array-like)
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>

typedef enum { ANY_T, STACK_T, QUEUE_T } structure_type_t;

typedef struct container_S {
    int *items;
    structure_type_t type;
    size_t allocated_size;
    size_t length;
} container_t, *container_p, stack_t, *stack_p, queue_t, *queue_p;

struct object_pool_S {
    container_p *objects;
    size_t size;
};

struct object_pool_S obj_pool = {NULL, 0};

bool container_ptr_valid(container_p ptr, structure_type_t type)
{
    if (ptr == NULL) return false;
    size_t i;
    for (i = 0; i < obj_pool.size; ++i) {
        if (obj_pool.objects[i] == ptr) {
            if (ptr->type == type || type == ANY_T)
                return true;
            return false;
        }
    }
    return false;
}

void free_obj_pool(void)
{
    while (obj_pool.size--) {
        free(obj_pool.objects[obj_pool.size]->items);
        free(obj_pool.objects[obj_pool.size]);
    }
    free(obj_pool.objects);
}

container_p new_container(structure_type_t type, size_t initial_size)
{
    container_p c = NULL;
    c = malloc(sizeof(container_t));
    if (c == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    container_p *new_obj_list = realloc(obj_pool.objects, sizeof(container_p) * (obj_pool.size + 1));
    if (new_obj_list == NULL) {
        free(c);
        errno = ENOMEM;
        return NULL;
    }
    if (!initial_size) initial_size = 1;
    c->items = malloc(sizeof(int) * initial_size);
    if (c->items == NULL) {
        free(c);
        free(new_obj_list);
        errno = ENOMEM;
        return NULL;
    }

    obj_pool.objects = new_obj_list;
    obj_pool.objects[obj_pool.size] = c;
    obj_pool.size++;
    c->length = 0;
    c->allocated_size = initial_size;
    c->type = type;

    return c;
}

void expand_container(container_p c, size_t new_size)
{
    if (c->allocated_size == new_size)
        return;
    if (c->allocated_size > new_size) {
        errno = EINVAL;
        return;
    }
    int *new_items = malloc(sizeof(int) * new_size);
    if (new_items == NULL) {
        errno = ENOMEM;
        return;
    }
    if (c->type == STACK_T)
        memcpy(new_items, c->items, c->length * sizeof(int));
    else if (c->type == QUEUE_T)
        memcpy((int *) new_items + new_size - c->length, (int *) c->items + c->allocated_size - c->length,
               c->length * sizeof(int));
    c->allocated_size = new_size;
    c->items = new_items;
}

inline bool is_stack(container_p ptr)
{
    return container_ptr_valid(ptr, STACK_T);
}

inline bool is_queue(container_p ptr)
{
    return container_ptr_valid(ptr, QUEUE_T);
}

bool empty(container_p ptr)
{
    if (!container_ptr_valid(ptr, ANY_T)) {
        errno = EINVAL;
        return true;
    }
    return !ptr->length;
}

size_t size(container_p ptr)
{
    if (!container_ptr_valid(ptr, ANY_T)) {
        errno = EINVAL;
        return 0;
    }
    return ptr->length;
}

container_p copy(container_p ptr)
{
    if (!container_ptr_valid(ptr, ANY_T)) {
        errno = EINVAL;
        return NULL;
    }
    errno = 0;
    container_p cc = new_container(ptr->type, ptr->allocated_size);
    if (cc == NULL) /* errno is set to ENOMEM */
        return NULL;
    memcpy(cc->items, ptr->items, sizeof(int) * ptr->allocated_size);
    cc->length = ptr->length;
    return cc;
}

inline stack_p new_stack(void)
{
    return new_container(STACK_T, 10);
}

inline queue_p new_queue(void)
{
    return new_container(QUEUE_T, 10);
}

int s_peek(stack_p s)
{
    if (!container_ptr_valid(s, STACK_T)) {
        errno = EINVAL;
        return 0;
    }
    if (s->length == 0) {
        errno = EINVAL;
        return 0;
    }
    return s->items[s->length - 1];
}

int s_pop(stack_p s)
{
    if (!container_ptr_valid(s, STACK_T)) {
        errno = EINVAL;
        return 0;
    }
    if (s->length == 0) {
        errno = EINVAL;
        return 0;
    }
    s->length -= 1;
    return s->items[s->length];
}

void s_push(stack_p s, int item)
{
    if (!container_ptr_valid(s, STACK_T)) {
        errno = EINVAL;
        return;
    }
    errno = 0;
    if (s->length == s->allocated_size)
        expand_container(s, s->allocated_size + s->allocated_size / 4);
    if (errno == ENOMEM || errno == EINVAL) {
        /* EINVAL would mean an overflow in the size_t occurred */
        errno = ENOMEM;
        return;
    }
    s->items[s->length] = item;
    s->length += 1;
}

void q_enqueue(queue_p q, int item)
{
    if (!container_ptr_valid(q, QUEUE_T)) {
        errno = EINVAL;
        return;
    }
    errno = 0;
    if (q->length == q->allocated_size)
        expand_container(q, q->allocated_size + q->allocated_size / 4);
    if (errno == ENOMEM || errno == EINVAL) {
        /* EINVAL would mean an overflow in the size_t occurred */
        errno = ENOMEM;
        return;
    }
    q->items[q->allocated_size - q->length - 1] = item;
    q->length += 1;
}

int q_dequeue(queue_p q)
{
    if (!container_ptr_valid(q, QUEUE_T)) {
        errno = EINVAL;
        return 0;
    }
    if (q->length == 0) {
        errno = EINVAL;
        return 0;
    }
    int item = q->items[q->allocated_size - 1];
    size_t i;
    for (i = 1; i < q->length; i += 1) {
        q->items[q->allocated_size - i] = q->items[q->allocated_size - i - 1];
    }
    q->length -= 1;
    return item;
}


/*
 *********************************
 *                               *
 * Assignment-specific functions *
 *                               *
 *********************************
 */


int maximum(queue_p q)
{
    int max = q_dequeue(q);
    while (!empty(q)) {
        int temp = q_dequeue(q);
        max = max > temp ? max : temp;
    }
    return max;
}

void swapFirstLast(queue_p q)
{
    /* Using abstractions provided by functions above, not directly manipulating the array */
    if (size(q) < 2)
        return;
    int first = q_dequeue(q);
    stack_p stemp = new_stack();
    stack_p stemp2 = new_stack();
    while (!empty(q))
        s_push(stemp, q_dequeue(q));
    int last = s_pop(stemp);
    while (!empty(stemp))
        s_push(stemp2, s_pop(stemp));
    q_enqueue(q, last);
    while (!empty(stemp2))
        q_enqueue(q, s_pop(stemp2));
    q_enqueue(q, first);
}

void insert(queue_p q, int val, int index)
{
    size_t s_index = (size_t) index;
    errno = 0;
    if (size(q) < s_index)
        errno = EINVAL;
    if (errno == EINVAL)
        return;
    queue_p q1 = new_queue();
    size_t i;
    for (i = 0; i < s_index; i += 1)
        q_enqueue(q1, q_dequeue(q));
    q_enqueue(q1, val);
    while (!empty(q))
        q_enqueue(q1, q_dequeue(q));
    while (!empty(q1))
        q_enqueue(q, q_dequeue(q1));
}

void reverseOdd(queue_p q)
{
    queue_p temp = copy(q);
    stack_p oddstack = new_stack();
    int o;
    while (!empty(q))
        if ((o = q_dequeue(q)) % 2)
            s_push(oddstack, o);
    while (!empty(temp))
        if ((o = q_dequeue(temp)) % 2)
            q_enqueue(q, s_pop(oddstack));
        else
            q_enqueue(q, o);
}

void reverse(queue_p q, int k)
{
    errno = 0;
    if (size(q) < k)
        errno = EINVAL;
    if (errno == EINVAL || k < 2)
        return;
    queue_p temp = new_queue();
    stack_p temp_s = new_stack();
    while (k--)
        s_push(temp_s, q_dequeue(q));
    while (!empty(q))
        q_enqueue(temp, q_dequeue(q));
    while (!empty(temp_s))
        q_enqueue(q, s_pop(temp_s));
    while (!empty(temp))
        q_enqueue(q, q_dequeue(temp));
}

/* input functions */

void question_1(void)
{
    printf("[maximum()] Please enter the queue (FIFO) - separate with newlines, terminate with an empty line:\n");
    queue_p q = new_queue();
    char buf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(buf, 10, stdin);
        int i;
        for (i = 0; i < strlen(buf); i += 1) {
            input_satisfied = false;
            if (buf[i] >= '0' && buf[i] <= '9') {
                input_satisfied = true;
                q_enqueue(q, atoi(buf));
                break;
            }
        }
    }
    printf("Max: %d", maximum(q));
}

void question_2(void)
{
    printf("[swapFirstLast()] Please enter the queue (FIFO) - separate with newlines, terminate with an empty line:\n");
    queue_p q = new_queue();
    char buf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(buf, 10, stdin);
        int i;
        for (i = 0; i < strlen(buf); i += 1) {
            input_satisfied = false;
            if (buf[i] >= '0' && buf[i] <= '9') {
                input_satisfied = true;
                q_enqueue(q, atoi(buf));
                break;
            }
        }
    }
    swapFirstLast(q);
    printf("New queue:\n");
    while (!empty(q))
        printf("%d ", q_dequeue(q));
}

void question_3(void)
{
    printf("[insert(k)] Please enter the queue (FIFO) - separate with newlines, terminate with an empty line:\n");
    queue_p q = new_queue();
    char buf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(buf, 10, stdin);
        int i;
        for (i = 0; i < strlen(buf); i += 1) {
            input_satisfied = false;
            if (buf[i] >= '0' && buf[i] <= '9') {
                input_satisfied = true;
                q_enqueue(q, atoi(buf));
                break;
            }
        }
    }
    int k, value;
    printf("Enter index k (0-based):\n");
    scanf("%d", &k);
    while (getchar() == ' ') {}
    printf("Enter value:\n");
    scanf("%d", &value);
    while (getchar() == ' ') {}
    errno = 0;
    insert(q, value, k);
    if (errno == EINVAL) {
        printf("Operation failed. Invalid index.");
        return;
    }
    printf("New queue:\n");
    while (!empty(q))
        printf("%d ", q_dequeue(q));
}

void question_4(void)
{
    printf("[reverseOdd()] Please enter the queue (FIFO) - separate with newlines, terminate with an empty line:\n");
    queue_p q = new_queue();
    char buf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(buf, 10, stdin);
        int i;
        for (i = 0; i < strlen(buf); i += 1) {
            input_satisfied = false;
            if (buf[i] >= '0' && buf[i] <= '9') {
                input_satisfied = true;
                q_enqueue(q, atoi(buf));
                break;
            }
        }
    }
    reverseOdd(q);
    printf("New queue:\n");
    while (!empty(q))
        printf("%d ", q_dequeue(q));
}

void question_5(void)
{
    printf("[reverse(k)] Please enter the queue (FIFO) - separate with newlines, terminate with an empty line:\n");
    queue_p q = new_queue();
    char buf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(buf, 10, stdin);
        int i;
        for (i = 0; i < strlen(buf); i += 1) {
            input_satisfied = false;
            if (buf[i] >= '0' && buf[i] <= '9') {
                input_satisfied = true;
                q_enqueue(q, atoi(buf));
                break;
            }
        }
    }
    int k, value;
    printf("Enter k - number of first elements to reverse:\n");
    scanf("%d", &k);
    while (getchar() == ' ') {}
    errno = 0;
    reverse(q, k);
    if (errno == EINVAL) {
        printf("Operation failed. Invalid index.");
        return;
    }
    printf("New queue:\n");
    while (!empty(q))
        printf("%d ", q_dequeue(q));
}

int main()
{
    atexit(free_obj_pool);
    uint8_t question;
    do {
        printf("Choose question (1,2,3,4,5): ");
        scanf("%d", &question);
        while (getchar() == ' ') {}
        switch (question) {
            case 1:
                question_1();
                break;
            case 2:
                question_2();
                break;
            case 3:
                question_3();
                break;
            case 4:
                question_4();
                break;
            case 5:
                question_5();
                break;
        }
    } while (question > 5);
    return 0;
}