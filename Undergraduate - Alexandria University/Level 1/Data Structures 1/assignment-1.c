#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <stdint.h>

typedef char *str_t;

typedef enum { INT, CHAR, FLOAT, STRING, UINT64, BIGINT } datatype_t;

typedef struct stack_s {
    datatype_t type;
    void *collection;
    size_t size;
    size_t next_index;
    bool dynamic;
} stack_t, *stack_p;

struct stack_pool_s {
    stack_p *stacks;
    size_t size;
};

struct stack_pool_s stack_pool = {NULL, 0};

stack_p new_stack(const datatype_t type, const size_t size, const bool is_dynamic)
{
    stack_p s = NULL;
    s = malloc(sizeof(stack_t));
    if (s == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    stack_p *new_stack_list = realloc(stack_pool.stacks, sizeof(stack_p) * (stack_pool.size + 1));
    if (new_stack_list == NULL) {
        free(s);
        errno = ENOMEM;
        return NULL;
    }
    stack_pool.stacks = new_stack_list;
    stack_pool.stacks[stack_pool.size] = s;
    stack_pool.size++;
    s->size = size;
    s->dynamic = is_dynamic;
    s->next_index = 0;
    s->type = type;
    s->collection = NULL;
    if (size == 0) return s;
    switch (type) {
        case INT:
            s->collection = malloc(sizeof(int) * size);
            break;
        case UINT64:
            s->collection = malloc(sizeof(uint64_t) * size);
            break;
        case CHAR:
            s->collection = malloc(sizeof(float) * size);
            break;
        case STRING:
            s->collection = malloc(sizeof(str_t) * size);
            break;
        case FLOAT:
            s->collection = malloc(sizeof(float) * size);
            break;
    }
    if (s->collection == NULL) {
        free(s);
        errno = ENOMEM;
        return NULL;
    }
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

void stack_push(stack_p s, void *elem)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return;
    }
    if (elem == NULL) {
        errno = EINVAL;
        return;
    }
    if (s->size == s->next_index) {
        if (!s->dynamic) {
            errno = ERANGE;
            return;
        }
        void *new_collection = NULL;
        switch (s->type) {
            case INT:
                new_collection = realloc(s->collection, sizeof(int) * (s->size + s->size / 2 + 1));
                break;
            case UINT64:
                new_collection = realloc(s->collection, sizeof(uint64_t) * (s->size + s->size / 2 + 1));
                break;
            case CHAR:
                new_collection = realloc(s->collection, sizeof(char) * (s->size + s->size / 2 + 1));
                break;
            case STRING:
                new_collection = realloc(s->collection, sizeof(str_t) * (s->size + s->size / 2 + 1));
                break;
            case FLOAT:
                new_collection = realloc(s->collection, sizeof(float) * (s->size + s->size / 2 + 1));
                break;
        }
        if (new_collection == NULL) {
            errno = ENOMEM;
            return;
        }
        s->collection = new_collection;
        s->size += s->size / 2 + 1;
    }
    s->next_index++;
    switch (s->type) {
        case INT:
            *((int *) s->collection + s->next_index) = *(int *) elem;
            break;
        case UINT64:
            *((uint64_t *) s->collection + s->next_index) = *(uint64_t *) elem;
            break;
        case CHAR:
            *((char *) s->collection + s->next_index) = *(char *) elem;
            break;
        case STRING:
            *((str_t *) s->collection + s->next_index) = malloc(sizeof(char) * (strlen(*(str_t *) elem) + 1));
            strcpy(*((str_t *) s->collection + s->next_index), *(str_t *) elem);
            break;
        case FLOAT:
            *((float *) s->collection + s->next_index) = *(float *) elem;
            break;
    }
}

bool stack_is_empty(stack_p s)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return true;
    }
    if (s->next_index == 0)
        return true;
    return false;
}

void stack_peek(stack_p s, size_t index, void* copy_addr)
{
    /* Copies the value at the specified index to the variable at the specified copy_addr */
    if (!stack_ptr_valid(s) || index > s->next_index-1 || stack_is_empty(s)) {
        errno = EINVAL;
        return;
    }
    switch (s->type) {
        case INT:
            *(int*) copy_addr = *((int *) s->collection + index);
            return;
        case UINT64:
            *(uint64_t*) copy_addr =  *((uint64_t *) s->collection + index);
            return;
        case CHAR:
            *(char*) copy_addr =  *((char *) s->collection + index);
            return;
        case STRING:
            str_t item =  *((str_t *) s->collection + index);
            if (item == NULL) {
                *(str_t *)copy_addr = NULL;
                return;
            }
            str_t item_copy = malloc(sizeof(str_t) * (strlen(item)+1));
            if (item_copy == NULL) {
                *(str_t *)copy_addr = NULL;
                errno = ENOMEM;
                return;
            }
            strcpy(item_copy, item);
            *(str_t*)copy_addr = item_copy;
        case FLOAT:
            *(float*) copy_addr =  *((float *) s->collection + index);
            return;
    }
}

void stack_pop(stack_p s, void* copy_addr)
{
    if (!stack_ptr_valid(s) || stack_is_empty(s)) {
        errno = EINVAL;
        return;
    }
    if (copy_addr == NULL && s->type == STRING) {
        free((str_t*)s->collection + s->next_index);
        s->next_index--;
        return;
    }
    switch (s->type) {
        case INT:
            *(int*)copy_addr = *((int *) s->collection + s->next_index);
            break;
        case UINT64:
            *(uint64_t*)copy_addr = *((uint64_t *) s->collection + s->next_index);
            break;
        case CHAR:
            *(char*)copy_addr = *((char *) s->collection + s->next_index);
            break;
        case STRING:
            *(str_t*)copy_addr = *((str_t *) s->collection + s->next_index);
            break;
        case FLOAT:
            *(float*)copy_addr = *((float *) s->collection + s->next_index);
            break;
    }
    s->next_index--;
}

size_t stack_len(stack_p s)
{
    if (!stack_ptr_valid(s)) {
        errno = EINVAL;
        return 0;
    }
    return s->next_index;
}

void delete_stack(stack_p s)
{
    size_t i = 0;
    while (i < stack_pool.size) {
        if (stack_pool.stacks[i] == s) {
            stack_p *new_stack_list = realloc(stack_pool.stacks, sizeof(stack_p) * (stack_pool.size + - 1));
            if (new_stack_list == NULL) {
                errno = ENOMEM;
                return;
            }
            free(s->collection);
            free(s);
            memcpy(new_stack_list, stack_pool.stacks, sizeof(stack_p) * i);
            memcpy(new_stack_list+i, stack_pool.stacks+i+1, sizeof(stack_p) * (stack_pool.size - i - 1));
            free(stack_pool.stacks);
            stack_pool.stacks = new_stack_list;
            return;
        }
    }
}

void free_stack_pool(void)
{
    size_t i;
    for (i = 0; i < stack_pool.size; ++i) {
        if (stack_pool.stacks[i]->collection != NULL) {
            if (stack_pool.stacks[i]->type == STRING) {
                while (!stack_is_empty(stack_pool.stacks[i])) {
                    str_t str = NULL;
                    stack_pop(stack_pool.stacks[i], &str);
                    free(str);
                }
            }
            free(stack_pool.stacks[i]->collection);
        }
        free(stack_pool.stacks[i]);
    }
    free(stack_pool.stacks);
}

str_t bgets(const char delim, datatype_t type)
{
    char *buffer = NULL, *newbuffer = NULL, c;
    size_t buffer_size = 21, len = 0;
    buffer = (char *) malloc(buffer_size * sizeof(char));
    if (!buffer) {
        errno = ENOMEM;
        return NULL;
    }
    while ((c = getchar()) != delim && c != EOF) {
        if (type == INT || type == BIGINT)
            if (c == '-' && len != 0) continue;
        if (type == INT || type == UINT64 || type == BIGINT) {
            if ((c < '0' || c > '9') && (c == '-' && type == UINT64)) continue;
            if (c == '0' && (len == 0 || (len == 1 && buffer[0] == '-'))) continue;
        }
        *(buffer + len++) = c;
        if (len == 20 && type == UINT64) break;
        if (len == 9 && type == INT) break;
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
    if (!(n % 2) && n != 2) return false;
    if (n == 2) return true;
    while (n % factor && factor * factor < n) factor += 2;
    return n % factor || n == factor;
}

/* Assignment-specific functions */

char bigint_cmp(str_t x, str_t y)
{
    size_t lx = strlen(x), ly = strlen(y);
    if (*x == '-' && *y != '-') return -1;
    if (*x != '-' && *y == '-') return 1;
    if (*x == '-' && *y == '-') {
        str_t tmp = x;
        x = y;
        y = tmp;
        size_t tmp_size = lx;
        lx = ly;
        ly = tmp_size;
        x++;
        y++;
        lx--;
        ly--;
    }
    if (lx > ly) return 1;
    if (lx < ly) return -1;
    while (x[lx] == y[ly] && lx != 0) {
        lx--;
        ly--;
    }
    if (x[lx] > y[ly]) return 1;
    if (x[lx] < y[ly]) return -1;
    return 0;
}

void reverse_string(str_t str)
{
    size_t i = 0;
    stack_p temp = new_stack(CHAR, strlen(str), false);
    while (str[i])
        stack_push(temp, str + i++);
    i = 0;
    while (!stack_is_empty(temp))
        stack_pop(temp, str + i++);
}

void question_1(void)
{
    /* Reversing a string using stack operations */
    printf("Enter string: ");
    str_t str = bgets('\n', STRING);
    reverse_string(str);
    printf("Reversed string: %s", str);
    free(str);
}

bool is_stack_sorted(stack_p s)
{
    bool sorted = true;
    if (!stack_is_empty(s) && stack_len(s) != 1) {
        str_t str_1 = NULL, str_2 = NULL;;
        stack_pop(s, &str_1);
        while (!stack_is_empty(s)) {
            stack_pop(s, &str_2);
            if (bigint_cmp(str_1, str_2) > 0) {
                sorted = false;
                break;
            }
            free(str_1);
            str_1 = str_2;
        }
        free(str_2);
    }
    return sorted;
}

void question_2(void)
{
    printf(
        "Enter a list of numbers forming a stack [input rules: newline-separated, bottom to top, bigint supported, negative supported, integral only]:\n");
    stack_p stk = new_stack(STRING, 100, true);
    str_t str = NULL;
    while ((str = bgets('\n', BIGINT)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        stack_push(stk, &str);
        free(str);
    }
    printf("The stack is %s", is_stack_sorted(stk) ? "sorted" : "not sorted.");
}

void question_3(void)
{
    printf("Enter a list of numbers forming a stack [input rules: newline-separated, bottom to top, uint_64]:\n");
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
    uint64_t num;
    while (!stack_is_empty(input)) {
        stack_pop(input, &num);
        printf("%lld\n", num);
    }
}

void question_4(void)
{
    printf(
        "Enter a list of numbers forming a stack [input rules: newline-separated, bottom to top, bigint supported, negative supported, integral only]:\n");
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
        stack_push(stk_1, &str);
        free(str);
    }
    printf(
        "Enter second list of numbers forming a stack [input rules: bottom to top, bigint supported, negative supported, integral only]:\n");
    while ((str = bgets('\n', BIGINT)) != NULL) {
        if (!strlen(str)) {
            free(str);
            break;
        }
        stack_push(stk_2, &str);
        free(str);
    }
    str_t n1 = NULL, n2 = NULL, smaller = NULL;
    while (!stack_is_empty(stk_1) || !stack_is_empty(stk_2) || n1 || n2) {
        if (n1 == NULL)
            stack_pop(stk_1, &n1);
        if (n2 == NULL)
            stack_pop(stk_2, &n2);
        if (n2 == NULL)
            n2 = n1;
        if (n1 == NULL)
            n1 = n2;
        smaller = bigint_cmp(n1, n2) >= 0 ? n2 : n1;
        stack_push(stk_3, &smaller);
        if (n1 == smaller)
            n1 = NULL;
        if (n2 == smaller)
            n2 = NULL;
        free(smaller);
    }
    str_t tmp;
    while (!stack_is_empty(stk_3)) {
        stack_pop(stk_3, &tmp);
        stack_push(stk_final, &tmp);
    }
    printf("Merged: ");
    while (!stack_is_empty(stk_final)) {
        stack_pop(stk_final, &str);
        printf("\n%s", str);
    }
}

bool check_balanced_parentheses(stack_p s)
{
    size_t num_open = 0;
    char c;
    while (!stack_is_empty(s)) {
        stack_pop(s, &c);
        if (c == ')') num_open++;
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
    printf("%s", check_balanced_parentheses(stk) ? "\nBalanced" : "\nUnbalanced");
}

int main()
{
    atexit(free_stack_pool);
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
