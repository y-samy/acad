/*
 * Assignment 5
 * Solution to Problem 1
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a5-1.c /std:c11           # produces a5-1.exe
 * gcc: gcc ./a5-1.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a5-1.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>
#include <stdlib.h>

#define WHITESPACE_C ' '
#define NEWLINE_C '\n'
#define MAX_STRING_LEN 10000
#define BUFFER_LEN 100
#define SPLIT_MARKER (-2)

char *bgets(char delim);
char *partially_tokenize(char *str, char delim);
char *split_and_join(char *str);

int main() {
    printf("Enter a newline-terminated string:\n");
    char* input_str = bgets(NEWLINE_C);
    char *output_str = split_and_join(input_str);
    printf("%s", output_str);
    free(input_str);
    free(output_str);
    return 0;
}

char *split_and_join(char *str) {
    char *token = NULL;
    while (*(token = partially_tokenize(str, WHITESPACE_C)))
        *token = SPLIT_MARKER;

    size_t len = 0;
    while (*(str + len++));

    char *output_str = malloc(len * sizeof(char)), c;
    len = 0;
    while((c = *(str++))) {
        if(c != SPLIT_MARKER) *(output_str + len++) = c;
    }
    *(output_str + len) = '\0';
    return output_str;
}

char *bgets(const char delim) {
    char *buffer = NULL, *newbuffer = NULL, c;
    size_t buffer_size = BUFFER_LEN, len = 0;
    buffer = (char *) malloc(buffer_size * sizeof(char));
    while ((c = getchar()) != delim && c != EOF) {
        *(buffer + len++) = c;
        if (len == buffer_size) {
            if (buffer_size > MAX_STRING_LEN) break;
            buffer_size += BUFFER_LEN;
            newbuffer = (char *) realloc(buffer, buffer_size * sizeof(char));
            if (!newbuffer) return buffer;
            buffer = newbuffer;
        }
    }
    *(buffer + len) = '\0';
    return buffer;
}

char *partially_tokenize(char *str, const char delim) {
    static char *string = NULL, *token = NULL;
    if (str != string) {
        token = string = str;
        return token;
    }
    while (*token) {
        if (*(token++) == delim) return token;
    }
    return token;
}