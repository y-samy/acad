/*
* Assignment 5
 * Solution to Problem 3
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a5-3.c /std:c11           # produces a5-3.exe
 * gcc: gcc ./a5-3.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a5-3.c -w --std=c11   # produces a.out or a.exe
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LEN 10000
#define BUFFER_LEN 100
#define NEWLINE_C '\n'
#define WHITESPACE_S " \t"
#define WHITESPACE_C ' '
#define NULL_C '\0'

int findFrequency(char *str, char *word);
char *bgets(char delim);
void detokenize(char *start_ptr, char* end_ptr, char delim);

int main() {
    printf("Enter newline-terminated string:\n");
    char *input_string = bgets(NEWLINE_C);
    printf("Enter the word to search for in the string:\n");
    char *word = bgets(NEWLINE_C);
    printf("The word occurred %d times in the provided string.", findFrequency(input_string, word));
    free(input_string);
    free(word);
    return 0;
}

int findFrequency(char *str, char *word) {
    char *end_ptr = NULL, *token = NULL;
    end_ptr = str + strlen(str);
    token = strtok(str, WHITESPACE_S);
    int freq = 0;
    while (token != NULL) {
        if (!strcmp(token, word)) ++freq;
        token = strtok(NULL, WHITESPACE_S);
    }
    detokenize(str, end_ptr, WHITESPACE_C);
    return freq;
}

void detokenize(char *start_ptr, char* end_ptr, char delim) {
    while (start_ptr < end_ptr) {
        if (!*start_ptr) *start_ptr = delim;
        ++start_ptr;
    }
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