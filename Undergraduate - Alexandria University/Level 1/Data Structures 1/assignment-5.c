/*
    Assignment 5 - Binary Search Trees
    Specifications:
        Language(s): C
        Standard(s): *
        Toolchain(s): GNU/ MSVC
        License(s): BSD-3 Clause
        BST Implementation: AVL
    Authors:
        Youssef Samy    - 9545; @y-samy
        Youssef Shaheen - 9627;
*/

/* Libraries: */
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _MSC_VER
#define strcasecmp _stricmp
#endif

/* AVL Implementation: */
#define MAX(x, y) ((x) > (y) ? (x) : (y))
#define WORD_MAX 100
typedef char *str;
typedef struct Node_S {
    char word[WORD_MAX];
    struct Node_S *l_child;
    struct Node_S *r_child;
    int height;
} Node, *Node_p;

Node_p new_node(str word)
{
    Node_p node = malloc(sizeof(Node));
    if (node == NULL) {
        errno = ENOMEM;
        return NULL;
    }
    strcpy(node->word, word);
    node->l_child = NULL;
    node->r_child = NULL;
    node->height = 1;
    return node;
}

void del_node(Node_p node) { free(node); }

void del_tree(Node_p root)
{
    if (root->l_child != NULL) {
        del_tree(root->l_child);
    }
    if (root->r_child != NULL) {
        del_tree(root->r_child);
    }
    del_node(root);
}

int tree_heightof(Node_p root)
{
    if (root == NULL)
        return 0;
    return root->height;
}

int tree_balanceof(Node_p root)
{
    if (root == NULL)
        return 0;
    return tree_heightof(root->l_child) - tree_heightof(root->r_child);
}

Node_p left_rotate(Node_p node)
{
    if (node == NULL)
        return NULL;
    if (node->r_child == NULL)
        return NULL;
    Node_p a = node;
    Node_p b = node->r_child;
    Node_p c = b->l_child;

    b->l_child = a;
    a->r_child = c;

    a->height = 1 + MAX(tree_heightof(a->l_child), tree_heightof(a->r_child));
    b->height = 1 + MAX(tree_heightof(b->l_child), tree_heightof(b->r_child));
    return b;
}

Node_p right_rotate(Node_p node)
{
    if (node == NULL)
        return NULL;
    if (node->l_child == NULL)
        return NULL;
    Node_p a = node;
    Node_p b = node->l_child;
    Node_p c = b->r_child;

    b->r_child = a;
    a->l_child = c;

    a->height = 1 + MAX(tree_heightof(a->l_child), tree_heightof(a->r_child));
    b->height = 1 + MAX(tree_heightof(b->l_child), tree_heightof(b->r_child));
    return b;
}

Node_p insert(Node_p root, str word)
{
    if (root == NULL) {
        return new_node(word);
    }
    int comp_result = strcasecmp(root->word, word);
    if (comp_result == 0) {
        return root;
    }
    if (comp_result > 0) {
        root->l_child = insert(root->l_child, word);
    } else if (comp_result < 0) {
        root->r_child = insert(root->r_child, word);
    }

    root->height = 1 + MAX(tree_heightof(root->r_child), tree_heightof(root->l_child));

    int balance = tree_balanceof(root);
    if (balance > 1) {
        comp_result = strcasecmp(word, root->l_child->word);
        if (comp_result < 0) {
            return right_rotate(root);
        } else if (comp_result > 0) {
            root->l_child = left_rotate(root->l_child);
            return right_rotate(root);
        }
    } else if (balance < -1) {
        comp_result = strcasecmp(word, root->r_child->word);
        if (comp_result > 0) {
            return left_rotate(root);
        } else if (comp_result < 0) {
            root->r_child = right_rotate(root->r_child);
            return left_rotate(root);
        }
    }

    return root;
}

int tree_sizeof(Node_p root)
{
    if (root == NULL)
        return 0;
    return 1 + tree_sizeof(root->l_child) + tree_sizeof(root->r_child);
}

Node_p find(Node_p root, str word)
{
    Node_p last_valid_node = NULL;
    Node_p current = root;

    while (current != NULL) {
        last_valid_node = current;
        int comparison_result = strcasecmp(word, current->word);

        if (comparison_result == 0) {
            return current;
        } else if (comparison_result < 0) {
            current = current->l_child;
        } else {
            current = current->r_child;
        }
    }
    return last_valid_node;
}

Node_p predecessor(Node_p root_node, str word)
{
    Node_p pred = NULL;
    Node_p current = root_node;
    while (current != NULL) {
        int comparison_result = strcasecmp(word, current->word);
        if (comparison_result > 0) {
            pred = current;
            current = current->r_child;
        } else if (comparison_result < 0) {
            current = current->l_child;
        } else {
            if (current->l_child != NULL) {
                Node_p temp = current->l_child;
                while (temp->r_child != NULL) {
                    temp = temp->r_child;
                }
                return temp;
            }
            return pred;
        }
    }
    return pred;
}


Node_p successor(Node_p root_node, str word)
{
    Node_p suc = NULL;
    Node_p current = root_node;
    while (current != NULL) {
        int comparison_result = strcasecmp(word, current->word);
        if (comparison_result < 0) {
            suc = current;
            current = current->l_child;
        } else if (comparison_result > 0) {
            current = current->r_child;
        } else {
            if (current->r_child != NULL) {
                Node_p temp = current->r_child;
                while (temp->l_child != NULL) {
                    temp = temp->l_child;
                }
                return temp;
            }
            return suc;
        }
    }
    return suc;
}

#define DICT_PATHNAME "Dictionary.txt"

Node_p load_dictionary(void)
{
    FILE *dict_file = fopen(DICT_PATHNAME, "r");
    if (dict_file == NULL) {
        errno = EBADF;
        return NULL;
    }
    char word[WORD_MAX];
    Node_p root = NULL;
    while (fgets(word, WORD_MAX, dict_file)) {
        int len = strlen(word);
        while (word[len - 1] == '\n' || word[len - 1] == '\r') {
            word[len - 1] = '\0';
            len--;
        }
        if (len > 0) {
            root = insert(root, word);
            if (root == NULL) {
                errno = ENOMEM;
                return NULL;
            }
        }
    }
    fclose(dict_file);
    return root;
}


int main()
{
    printf("Loading dictionary..\n");
    Node_p dictionary_tree = load_dictionary();
    if (dictionary_tree == NULL) {
        if (errno == EBADF)
            printf("Error loading dictionary from file.\n");
        else if (errno == ENOMEM)
            printf("Error creating dictionary tree.\n");
        printf("Exiting..\n");
        return 1;
    }
    printf("Dictionary loaded successfully.\n");
    printf("-------------------------------\n");
    printf("Dictionary Stats:\n");
    printf("\tSize = %d\n", tree_sizeof(dictionary_tree));
    printf("\tHeight = %d\n", tree_heightof(dictionary_tree));
    printf("-------------------------------\n");
    printf("Enter a sentence:\n");
    str sentence = malloc(WORD_MAX * 10);
    fgets(sentence, WORD_MAX * 10, stdin);
    int len = strlen(sentence);
    while (sentence[len - 1] == '\n' || sentence[len - 1] == '\r' || sentence[len - 1] == ' ') {
        sentence[len - 1] = '\0';
        len--;
    }
    str word = strtok(sentence, " ");
    while (word != NULL) {
        if (find(dictionary_tree, word) != NULL) {
            if (!strcasecmp(word, find(dictionary_tree, word)->word))
                printf("%s - CORRECT\n", word);
            else {
                str closest = find(dictionary_tree, word)->word;
                printf("%s - INCORRECT, Suggestions: %s, %s, %s\n", word, closest,
                       predecessor(dictionary_tree, closest)->word, successor(dictionary_tree, closest)->word);
            }
        } else {
            printf("%s - INCORRECT\n", word);
        }
        word = strtok(NULL, " ");
    }
    free(sentence);
    return 0;
}
