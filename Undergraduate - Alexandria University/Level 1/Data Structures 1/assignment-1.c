#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

typedef enum {INT, CHAR, FLOAT, STRING, UINT64, BIGINT} datatype_t;
typedef char* str_t;

typedef struct bigint_s {
    str_t num;
    bool negative;
} bigint_t;

typedef struct stack_s {
    datatype_t type;
    void* collection;
    size_t size;
    size_t top_index;
    bool dynamic;
} stack_t, *stack_p;

struct stack_pool_s {
    stack_p* stacks;
    size_t size;
};

struct stack_pool_s stack_pool = {NULL, 0};

stack_p new_stack(const datatype_t type, const size_t upper_bound, const bool is_dynamic)
{
    stack_p s = NULL;
    s = malloc(sizeof(stack_t));
    if (s == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    stack_p* new_stack_list = realloc(stack_pool.stacks, sizeof(stack_p) * (stack_pool.size+1));
    if (new_stack_list == NULL) {
        free(s);
        errno = ENOMEM;
        return NULL;
    }
    stack_pool.stacks = new_stack_list;
    stack_pool.stacks[stack_pool.size] = s;
    stack_pool.size++;
    switch (type) {
        case INT:
            s->collection = malloc(sizeof(int) * (upper_bound+1));
            break;
        case UINT64:
            s->collection = malloc(sizeof(uint64_t) * (upper_bound+1));
            break;
        case CHAR:
            s->collection = malloc(sizeof(float) * (upper_bound+1));
            break;
        case STRING:
            s->collection = malloc(sizeof(str_t) * (upper_bound+1));
            break;
        case FLOAT:
            s->collection = malloc(sizeof(float) * (upper_bound+1));
            break;
    }
    if (s->collection == NULL) {
        free(s);
        errno = ENOMEM;
        return NULL;
    }
    s->size = upper_bound+1;
    s->dynamic = is_dynamic;
    s->top_index = 0;
    s->type = type;
    return s;
}

bool stack_ptr_valid(stack_p s)
{
    if (s == NULL) return false;
    size_t i;
    for (i = 0; i < stack_pool.size; ++i) {
        if (stack_pool.stacks[i] == s) return true;
    }
    return false;
}

void stack_push(stack_p s, void* elem)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return;
    }
    if (elem == NULL && s->type != STRING) {
        errno = EINVAL;
        return;
    }
    if (s->size == s->top_index) {
        if (!s->dynamic) {
            errno = ERANGE;
            return;
        }
        void* new_collection = NULL;
        switch (s->type) {
            case INT:
                new_collection = realloc(s->collection, sizeof(int) * (s->size + 50));
                break;
            case UINT64:
                new_collection = realloc(s->collection, sizeof(uint64_t) * (s->size + 50));
                break;
            case CHAR:
                new_collection = realloc(s->collection, sizeof(char) * (s->size + 50));
                break;
            case STRING:
                new_collection = realloc(s->collection, sizeof(str_t) * (s->size + 50));
                break;
            case FLOAT:
                new_collection = realloc(s->collection, sizeof(float) * (s->size + 50));
                break;
        }
        if (new_collection == NULL) {
            errno = ENOMEM;
            return;
        }
        s->collection = new_collection;
        s->size += 50;
    }
    s->top_index++;
    switch (s->type) {
        case INT:
            *((int*) s->collection + s->top_index) = *(int*)elem;
            break;
        case UINT64:
            *((uint64_t*) s->collection + s->top_index) = *(uint64_t*)elem;
            break;
        case CHAR:
            *((char*) s->collection + s->top_index) = *(char*)elem;
            break;
        case STRING:
            *((str_t*) s->collection + s->top_index) = malloc(sizeof(char) * (strlen((str_t) elem)+1));
            strcpy(*((str_t*) s->collection + s->top_index), (str_t) elem);
            break;
        case FLOAT:
            *((float*) s->collection + s->top_index) = *((float*)elem);
            break;
    }
}

bool stack_is_empty(stack_p s)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return true;
    }
    if (s->top_index == 0)
        return true;
    return false;
}

void* stack_peek(stack_p s, size_t index)
{
    if (!stack_ptr_valid(s) || index > s->top_index || stack_is_empty(s)) {
        errno = EINVAL;
        return NULL;
    }
    switch (s->type) {
        case INT:
            return (int*) s->collection + index;
        case UINT64:
            return (uint64_t*) s->collection + index;
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
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return NULL;
    }
    if (stack_is_empty(s))
        return NULL;
    void* item = NULL;
    switch (s->type) {
        case INT:
            item = (int*) s->collection + s->top_index;
            break;
        case UINT64:
            item = (uint64_t*) s->collection + s->top_index;
            break;
        case CHAR:
            item = (char*) s->collection + s->top_index;
            break;
        case STRING:
            item = (str_t*) s->collection + s->top_index;
            break;
        case FLOAT:
            item = (float*) s->collection + s->top_index;
            break;
    }
    s->top_index--;
    return item;
}

inline size_t stack_size(stack_p s)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return 0;
    }
    return s->top_index-1;
}

void free_stack_pool(void)
{
    size_t i;
    for (i = 0; i < stack_pool.size; ++i) {
        if (stack_pool.stacks[i]->collection != NULL) {
            if (stack_pool.stacks[i]->type == STRING) {
                while (!stack_is_empty(stack_pool.stacks[i]))
                    free(*(str_t*)stack_pop(stack_pool.stacks[i]));
            }
            free(stack_pool.stacks[i]->collection);
        }
        free(stack_pool.stacks[i]);
    }
    free(stack_pool.stacks);
}

str_t bgets(const char delim, datatype_t type) {
    char *buffer = NULL, *newbuffer = NULL, c;
    size_t buffer_size = 21, len = 0;
    buffer = (char *) malloc(buffer_size * sizeof(char));
    if (!buffer) {
        errno = ENOMEM;
        return NULL;
    }
    while ((c = getchar()) != delim && c != EOF) {
        if (type == INT)
            if (c == '-' && len != 0) continue;
        if (type == INT || type == UINT64) {
            if (c < '0' || c > '9') continue;
            if (c == '0' && (len == 0 || buffer[0] == '-')) continue;
        }
        *(buffer + len++) = c;
        if (len == 20 && type == UINT64) break;
        if (len == buffer_size) {
            buffer_size += 50;
            newbuffer = (char *) realloc(buffer, buffer_size * sizeof(char));
            if (!newbuffer) {
                errno = ENOMEM;
                return buffer;
            }
            buffer = newbuffer;
        }
    }
    *(buffer + len) = '\0';
    return buffer;
}

bool is_prime(const uint64_t n)
{
    uint64_t factor = 3;
    if (n < 2) return false;
    if (!(n%2) && n != 2) return false;
    if (n == 2) return true;
    while (n%factor && factor*factor < n) factor += 2;
    return n%factor || n == factor;
}

/* Assignment-specific functions */

void reverse_string(str_t str)
{
    size_t i = 0;
    stack_p temp = new_stack(CHAR, strlen(str), false);
    while (str[i])
        stack_push(temp, str + i++);
    i = 0;
    while (!stack_is_empty(temp))
        str[i++] = *(char*)stack_pop(temp);
}

void question_1(void)
{
    /* Reversing a string using stack operations */
    printf("Enter first string: ");
    str_t str = bgets('\n', STRING);
    reverse_string(str);
    printf("Reversed string: %s", str);
    free(str);
}

bool is_stack_sorted(stack_p s)
{
    bool sorted = true;
    if (!stack_is_empty(s) || stack_size(s) != 1) {
        str_t str_1 = *(str_t*)stack_pop(s);
        while (!stack_is_empty(s)) {
            str_t str_2 = *(str_t*)stack_pop(s);
            if (strcmp(str_1, str_2) > 0) {
                sorted = false;
                break;
            }
            str_1 = str_2;
        }
    }
    return sorted;
}

void question_2(void)
{
    printf("Enter a list of numbers forming a stack [input rules: bottom to top, bigint supported, negative supported, integral only]:\n");
    stack_p stk = new_stack(STRING, 100, true);
    str_t str = NULL;
    while ((str = bgets('\n', BIGINT)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        stack_push(stk, str);
        free(str);
    }
    printf("The stack is %s", is_stack_sorted(stk)?"sorted":"not sorted.");
}

void question_3(void)
{
    printf("Enter a list of numbers forming a stack [input rules: bottom to top, uint_64]:\n");
    stack_p input = new_stack(UINT64, 100, true);
    str_t str = NULL;
    uint64_t buffer = 0;
    while ((str = bgets('\n', UINT64)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        buffer = atoll(str);
        if (!is_prime(buffer)) stack_push(input, &buffer);
        free(str);
    }
    while (!stack_is_empty(input))
        printf("%lld\n", *(uint64_t*)stack_pop(input));
}

void question_4(void)
{
    printf("Enter a list of numbers forming a stack [input rules: bottom to top, bigint supported, negative supported, integral only]:\n");
    stack_p stk_1 = new_stack(STRING, 100, true);
    stack_p stk_2 = new_stack(STRING, 100, true);
    stack_p stk_3 = new_stack(STRING, 100, true);
    stack_p stk_final = new_stack(STRING, 100, true);
    str_t str = NULL;
    while ((str = bgets('\n', BIGINT)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        stack_push(stk_1, str);
        free(str);
    }
    printf("Enter second list of numbers forming a stack [input rules: bottom to top, bigint supported, negative supported, integral only]:\n");
    while ((str = bgets('\n', BIGINT)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        stack_push(stk_2, str);
        free(str);
    }
    str_t n1 = NULL, n2 = NULL, smaller = NULL;
    while (!stack_is_empty(stk_1) || !stack_is_empty(stk_2) || n1 || n2) {
        if (n1 == NULL)
            if ((n1 = stack_pop(stk_1)) != NULL)
                n1 = *(str_t*) n1;
        if (n2 == NULL)
            if ((n2 = stack_pop(stk_2)) != NULL)
                n2 = *(str_t*) n2;
        if (n2 == NULL)
            n2 = n1;
        if (n1 == NULL)
            n1 = n2;
        smaller = strcmp(n1,n2)>=0?n2:n1;
        stack_push(stk_3, smaller);
        if (n1 == smaller)
            n1 = NULL;
        if (n2 == smaller)
            n2 = NULL;
    }
    while (!stack_is_empty(stk_3))
        stack_push(stk_final, *(str_t*)stack_pop(stk_3));
    printf("Merged: ");
    while (!stack_is_empty(stk_final))
        printf("\n%s", *(str_t*) stack_pop(stk_final));

}

bool check_balanced_parentheses(stack_p s)
{
    size_t num_open = 0;
    char c;
    while (!stack_is_empty(s)) {
        if ((c= *(char*) stack_pop(s)) == ')') num_open++;
        else if (c == '(')
            if (!num_open) return false;
            else num_open--;
    }
    if (num_open) return false;
    return true;
}

void question_5(void)
{
    printf("Enter string to check for paranthesis balance:\n");
    stack_p stk = new_stack(CHAR, 100, true);
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
        stack_push(stk, &c);
    printf("%s", check_balanced_parentheses(stk)?"\nBalanced":"\nUnbalanced");
}

int main()
{
    atexit(free_stack_pool);
    uint8_t question;
    do {
        printf("Choose question (1,2,3,4,5): ");
        scanf("%d", &question);
        while (getchar() == ' ');
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