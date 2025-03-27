/*
 *
 * AUTHOR: Youssef Samy
 * @GITHUB: y-samy
 * @GITLAB: y-samy
 * LICENSE: BSD-3-CLAUSE
 * WARRANTY: NONE
 *
 * Assignment  on integer linked-lists
 *
 * PREFERABLY USE THE GNU-TOOLCHAIN BY
 * USING  A  COMPATIBLE  COMPILER (e.g
 * GCC/ CLang)
 *
 * STRICTLY USE A C23-STANDARD COMPATIBLE
 * COMPILER.  FOR EXAMPLES OF COMPILATION
 * COMMANDS WHEN USING GCC:
 *
 * gcc -std=c23 assignment-3.c
 * gcc -std=c2x assignment-3.c
 *
 */

// BEGIN OBJECTS & SMART POINTERS

#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define any_p void*
#define type_hint_t size_t

typedef struct obj_S {
    any_p  ptr;
    size_t reference_count;
    void   (*ref_count_decrement)(any_p);
    void   (*ref_count_increment)(any_p);
    void   (*destructor)(any_p);
    any_p  (*copy)(any_p);
    bool   (*empty)(any_p);

    type_hint_t type_hint;
    size_t      data_byte_size;
} *obj, obj_t;

struct object_pool_S {
    bool atexit_registered;
    obj* objects;
    size_t length;
};

struct object_pool_S obj_pool = {.atexit_registered = false, .objects = nullptr, .length = 0};

void cleanup_obj_pool(void)
{
    // Fall-back function when compiled with compilers not using the GNU toolchain
    // Frees all allocated objects at exit, doesn't otherwise prevent memory leaks
    for (size_t i = 0; i < obj_pool.length; i+=1) {
        if (obj_pool.objects[i]->destructor != nullptr)
            obj_pool.objects[i]->destructor(obj_pool.objects[i]->ptr);
        else
            free(obj_pool.objects[i]->ptr);
        free(obj_pool.objects[i]);
    }
    free(obj_pool.objects);
}

void register_obj(struct obj_S object)
{
    errno = 0;
    obj op = malloc(sizeof(obj_t));
    *op = object;
    obj* new_obj_list = realloc(obj_pool.objects, sizeof(obj) * (obj_pool.length + 1));
    if (new_obj_list == nullptr) {
        errno = ENOMEM;
        return;
    }
    obj_pool.objects = new_obj_list;
    obj_pool.objects[obj_pool.length] = op;
    obj_pool.length += 1;
    if (obj_pool.atexit_registered == false) {
        atexit(cleanup_obj_pool);
        obj_pool.atexit_registered = true;
    }
}

void obj_cleanup(any_p* var_pp)
{
    if (*var_pp == nullptr)
        return;

    obj object = nullptr;
    for (size_t i = 0; i < obj_pool.length; i+=1) {
        if (obj_pool.objects[i]->ptr == *var_pp) {
            object = obj_pool.objects[i];
            break;
        }
    }

    if (object == nullptr)
        return;

    if (object->reference_count == 0) {
        if (object->destructor != nullptr)
            object->destructor(object->ptr);
        else
            free(object->ptr);
        obj* new_obj_list = malloc(sizeof(obj) * (obj_pool.length - 1));
        if (new_obj_list == nullptr) {
            for (size_t i = 0; i < obj_pool.length; i+=1) {
                if (obj_pool.objects[i] == object)
                    obj_pool.objects[i] = nullptr;
            }
            free(object);
            errno = ENOMEM;
            return;
        }
        for (size_t i = 0, j = 0; i < obj_pool.length; i+=1) {
            if (obj_pool.objects[i] != object)
                new_obj_list[j++] = obj_pool.objects[i];
        }
        free(object);
        free(obj_pool.objects);
        obj_pool.objects = new_obj_list;
        obj_pool.length -= 1;
    }
    else if (object->ref_count_decrement != nullptr)
        object->ref_count_decrement(object);
    else
        object->reference_count -= 1;
}

any_p shared_ptr(any_p ptr)
{
    if (ptr == nullptr)
        return nullptr;
    any_p ret_ptr = nullptr;
    obj tracking_obj = nullptr;
    for (size_t i = 0; i < obj_pool.length; i+=1) {
        if (obj_pool.objects[i]->ptr == ptr) {
            ret_ptr = ptr;
            tracking_obj = obj_pool.objects[i];
            break;
        }
    }

    // If the pointer has no registered object, return as-is
    if (ret_ptr == nullptr)
        return ptr;

    // Else, increment the reference count
    if (tracking_obj->ref_count_increment != nullptr)
        tracking_obj->ref_count_increment(tracking_obj);
    else
        tracking_obj->reference_count += 1;
    return ptr;
}

#define smart [[gnu::cleanup(obj_cleanup)]]

#define type_hint_any 0

bool valid_ptr(any_p ptr, type_hint_t type)
{
    if (ptr == nullptr)
        return false;

    obj corresponding_obj = nullptr;
    for (size_t i = 0; i < obj_pool.length; i += 1) {
        if (obj_pool.objects[i]->ptr == ptr) {
            corresponding_obj = obj_pool.objects[i];
            break;
        }
    }
    if (corresponding_obj == nullptr)
        return false;
    if (type == type_hint_any)
        return true;
    return (corresponding_obj->type_hint == type);
}

obj get_obj(any_p ptr, type_hint_t type)
{
    if (ptr == nullptr)
        return nullptr;

    obj corresponding_obj = nullptr;
    for (size_t i = 0; i < obj_pool.length; i += 1) {
        if (obj_pool.objects[i]->ptr == ptr) {
            corresponding_obj = obj_pool.objects[i];
            break;
        }
    }
    if (corresponding_obj == nullptr)
        return nullptr;
    if (type == type_hint_any || corresponding_obj->type_hint == type)
        return corresponding_obj;
    return nullptr;
}

bool empty(any_p ptr)
{
    obj object = nullptr;
    if ((object = get_obj(ptr, type_hint_any)) == nullptr)
        return true;
    if (object->empty == nullptr)
        return true;
    return object->empty(object->ptr);
}

// END OF OBJECTS & SMART POINTERS

// BEGIN LINKED LISTS

// Set the type hint for nodes from a unique function address
void typegen_node_i32(void) {}
#define node_i32_type ((type_hint_t) &typegen_node_i32)

typedef struct node_i32_S {
    struct node_i32_S* next_node;
    int32_t value;
} *node_i32_p, node_i32_t;


[[nodiscard]] node_i32_p new_node(int32_t value)
{
    smart node_i32_p node = malloc(sizeof(node_i32_t));
    if (node == nullptr)
        return nullptr;
    node->value = value;
    node->next_node = nullptr;
    struct obj_S node_obj = {
        .ptr = node,
        .type_hint = node_i32_type,
        .data_byte_size = sizeof(node_i32_t),
        .reference_count = 1,
        .destructor = nullptr,
        .copy = nullptr,
        .ref_count_decrement = nullptr,
        .ref_count_increment = nullptr,
        .empty = nullptr
    };
    register_obj(node_obj);
    return node;
}

void typegen_ll_i32(void) {}
#define ll_i32_type ((type_hint_t) &typegen_node_i32)

typedef struct ll_i32_S {
    node_i32_p head;
} *ll_i32_p, ll_i32_t;

void cleanup_ll(ll_i32_p ll)
{
    node_i32_p node = ll->head;
    node_i32_p nn = node;
    while (node != nullptr) {
        nn = node->next_node;
        obj_cleanup(&node);
        node = nn;
    }
    free(ll);
}

bool is_empty_ll(ll_i32_p ll)
{
    return ll->head == nullptr;
}

size_t length_ll(ll_i32_p ll)
{
    size_t len = 0;
    node_i32_p n = ll->head;
    while (n != nullptr) {
        len += 1;
        n = n->next_node;
    }
    return len;
}

[[nodiscard]] ll_i32_p new_linked_list(void)
{
    errno = 0;
    smart ll_i32_p ll = malloc(sizeof(ll_i32_t));
    if (ll == nullptr) {
        errno = ENOMEM;
        return nullptr;
    }
    ll->head = nullptr;
    struct obj_S ll_obj = {
        .ptr = ll,
        .type_hint = ll_i32_type,
        .data_byte_size = sizeof(ll_i32_t),
        .reference_count = 1,
        .destructor = &cleanup_ll,
        .copy = nullptr,
        .ref_count_decrement = nullptr,
        .ref_count_increment = nullptr,
        .empty = &is_empty_ll
    };
    register_obj(ll_obj);
    return ll;
}

void push_back(ll_i32_p list, int32_t val)
{
    // Usage: push_back(smart_ptr(LL), val);
    smart ll_i32_p ll = list;
    if (ll->head == nullptr) {
        ll->head = new_node(val);
        return;
    }
    node_i32_p n = ll->head;
    while (n != nullptr) {
        if (n->next_node == nullptr) {
            n->next_node = new_node(val);
            return;
        }
        n = n->next_node;
    }
}

// END LINKED LISTS

// BEGIN ASSIGNMENT FUNCTIONS

[[nodiscard]] node_i32_p search(ll_i32_p list, int32_t value)
{
    // Usage: smart node_i32_p node = search(shared_ptr(linked_list), val);
    smart ll_i32_p ll = list;
    errno = 0;
    if (!valid_ptr(ll, ll_i32_type)) {
        errno = EINVAL;
        return nullptr;
    }
    node_i32_p n = ll->head;
    while (n != nullptr) {
        if (n->value == value)
            return shared_ptr(n);
        n = n->next_node;
    }
    return nullptr;
}

void insert(ll_i32_p list, size_t index, int32_t value)
{
    // Usage: insert(shared_ptr(linked_list), index, value);
    smart ll_i32_p ll = list;
    errno = 0;
    if (!valid_ptr(ll, ll_i32_type)) {
        errno = EINVAL;
        return;
    }
    if (index > length_ll(ll)) {
        errno = EINVAL;
        return;
    }
    node_i32_p n = new_node(value);
    if (n == nullptr)
        return; // errno == ENOMEM

    if (index == 0) {
        n->next_node = ll->head;
        ll->head = n;
        return;
    }
    node_i32_p nn = ll->head;
    while (index -= 1)
        nn = nn->next_node;
    node_i32_p nnn = nn->next_node;
    nn->next_node = n;
    n->next_node = nnn;
}

bool identical(ll_i32_p x, ll_i32_p y)
{
    // Usage: identical(shared_ptr(list_1), shared_ptr(list_2));
    errno = 0;
    smart ll_i32_p lx = x;
    smart ll_i32_p ly = y;
    if (!valid_ptr(lx, ll_i32_type) || !valid_ptr(ly, ll_i32_type)) {
        errno = EINVAL;
        return false;
    }
    if (length_ll(lx) != length_ll(ly))
        return false;
    node_i32_p nx = lx->head, ny = ly->head;
    while (nx != nullptr && ny != nullptr) {
        if (nx->value != ny->value)
            return false;
        nx = nx->next_node;
        ny = ny->next_node;
    }
    return true;
}

[[nodiscard]] ll_i32_p merge(ll_i32_p x, ll_i32_p y)
{
    // Usage: merge(shared_ptr(list_1), shared_ptr(list_2));
    // Merges two ascendingly sorted lists into one sorted list
    errno = 0;
    smart ll_i32_p lx = x;
    smart ll_i32_p ly = y;
    if (!valid_ptr(lx, ll_i32_type) || !valid_ptr(ly, ll_i32_type)) {
        errno = EINVAL;
        return nullptr;
    }
    smart ll_i32_p ret = new_linked_list();
    node_i32_p nx = lx->head, ny = ly->head, nr = ret->head;
    while (nx != nullptr || ny != nullptr) {
        if (nx == nullptr) {
            while (ny != nullptr) {
                if (ret->head == nullptr) {
                    ret->head = new_node(ny->value);
                    nr = ret->head;
                }
                else {
                    nr->next_node = new_node(ny->value);
                    nr = nr->next_node;
                }
                ny = ny->next_node;
            }
            break;
        }
        if (ny == nullptr) {
            while (nx != nullptr) {
                if (ret->head == nullptr) {
                    ret->head = new_node(nx->value);
                    nr = ret->head;
                }
                else {
                    nr->next_node = new_node(nx->value);
                    nr = nr->next_node;
                }
                nx = nx->next_node;
            }
            break;
        }

        if (nx->value < ny->value) {
            if (ret->head == nullptr) {
                ret->head = new_node(nx->value);
                nr = ret->head;
            }
            else {
                nr->next_node = new_node(nx->value);
                nr = nr->next_node;
            }
            nx = nx->next_node;
        } else {
            if (ret->head == nullptr) {
                ret->head = new_node(ny->value);
                nr = ret->head;
            }
            else {
                nr->next_node = new_node(ny->value);
                nr = nr->next_node;
            }
            ny = ny->next_node;
        }
    }
    return shared_ptr(ret);
}

ll_i32_p intersection(ll_i32_p x, ll_i32_p y)
{
    // Usage: intersection(shared_ptr(list_1), shared_ptr(list_2));
    errno = 0;
    smart ll_i32_p lx = x;
    smart ll_i32_p ly = y;
    if (!valid_ptr(lx, ll_i32_type) || !valid_ptr(ly, ll_i32_type)) {
        errno = EINVAL;
        return nullptr;
    }
    smart ll_i32_p ret = new_linked_list();
    node_i32_p nx = lx->head, ny = ly->head, nr = ret->head;
    while (nx != nullptr && ny != nullptr) {
        if (nx->value < ny->value) {
            nx = nx->next_node;
            continue;
        }
        if (ny->value < nx->value) {
            ny = ny->next_node;
            continue;
        }
        if (ret->head == nullptr) {
            ret->head = new_node(ny->value);
            nr = ret->head;
        }
        else {
            nr->next_node = new_node(ny->value);
            nr = nr->next_node;
        }
        ny = ny->next_node;
        nx = nx->next_node;

    }
    return shared_ptr(ret);
}


// END ASSIGNMENT FUNCTIONS

void question_1(void)
{
    smart ll_i32_p ll = new_linked_list();
    printf("[search()] Enter the linked list, node by node from the beginning. Terminate each entry with a newline, terminate input with an empty line.\n");
    char intbuf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(ll), atoi(intbuf));
                break;
            }
        }
    }
    int32_t val;
    printf("Enter value to search for: ");
    scanf("%d", &val);
    while (getchar() == ' ') {}
    smart node_i32_p n = search(shared_ptr(ll), val);
    if (n == nullptr)
        printf("Value %d not found in linked list.", val);
    else
        printf("Value %d was found. Node address: %llu", val, (uint64_t) n);

}
void question_2(void)
{
    smart ll_i32_p ll = new_linked_list();
    printf("[insert()] Enter the linked list, node by node from the beginning. Terminate each entry with a newline, terminate input with an empty line.\n");
    char intbuf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(ll), atoi(intbuf));
                break;
            }
        }
    }
    int32_t index;
    printf("Enter index to insert at (0-based): ");
    scanf("%d", &index);
    while (getchar() == ' ') {}
    if (length_ll(ll) < index) {
        printf("Invalid index provided. Terminating.\n");
        return;
    }
    int32_t val;
    printf("Enter value: ");
    scanf("%d", &val);
    while (getchar() == ' ') {}
    insert(shared_ptr(ll), index, val);
    printf("New list:\n");
    node_i32_p n = ll->head;
    while (n != nullptr) {
        printf("%d ", n->value);
        n = n->next_node;
    }


}
void question_3(void)
{
    smart ll_i32_p l1 = new_linked_list();
    smart ll_i32_p l2 = new_linked_list();
    printf("[identical()] Enter the first linked list, node by node from the beginning. Terminate each entry with a newline, terminate input with an empty line.\n");
    char intbuf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l1), atoi(intbuf));
                break;
            }
        }
    }
    printf("Enter second linked list:\n");
    input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l2), atoi(intbuf));
                break;
            }
        }
    }

    if (identical(shared_ptr(l1), shared_ptr(l2)))
        printf("Lists are identical\n");
    else
        printf("Lists are different\n");
}

void question_4(void)
{
    smart ll_i32_p l1 = new_linked_list();
    smart ll_i32_p l2 = new_linked_list();
    smart ll_i32_p merged = nullptr;
    printf("[merge()] Enter the first linked list, node by node from the beginning. Terminate each entry with a newline, terminate input with an empty line.\n");
    char intbuf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l1), atoi(intbuf));
                break;
            }
        }
    }
    printf("Enter second linked list:\n");
    input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l2), atoi(intbuf));
                break;
            }
        }
    }

    merged = merge(shared_ptr(l1), shared_ptr(l2));
    printf("Merged list:\n");
    if (merged != nullptr){
        node_i32_p n = merged->head;
        while (n != nullptr) {
            printf("%d ", n->value);
            n = n->next_node;
        }
    }
}
void question_5(void)
{
    smart ll_i32_p l1 = new_linked_list();
    smart ll_i32_p l2 = new_linked_list();
    smart ll_i32_p isec = nullptr;
    printf("[intersection()] Enter the first linked list, node by node from the beginning. Terminate each entry with a newline, terminate input with an empty line.\n");
    char intbuf[10] = {};
    bool input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l1), atoi(intbuf));
                break;
            }
        }
    }
    printf("Enter second linked list:\n");
    input_satisfied = true;
    while (input_satisfied) {
        fgets(intbuf, 10, stdin);
        int i;
        for (i = 0; i < strlen(intbuf); i += 1) {
            input_satisfied = false;
            if (intbuf[i] >= '0' && intbuf[i] <= '9') {
                input_satisfied = true;
                push_back(shared_ptr(l2), atoi(intbuf));
                break;
            }
        }
    }

    isec = intersection(shared_ptr(l1), shared_ptr(l2));
    printf("Intersection of lists:\n");
    if (isec != nullptr){
        node_i32_p n = isec->head;
        while (n != nullptr) {
            printf("%d ", n->value);
            n = n->next_node;
        }
    }
}


int main()
{
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
