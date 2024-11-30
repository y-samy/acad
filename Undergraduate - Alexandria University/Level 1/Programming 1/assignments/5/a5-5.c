/*
* Assignment 5
 * Solution to Problem 5
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a5-5.c /std:c11           # produces a5-5.exe
 * gcc: gcc ./a5-5.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a5-5.c -w --std=c11   # produces a.out or a.exe
 */


#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING_LEN 10000
#define BUFFER_LEN 100
#define NEWLINE_C '\n'
#define WHITESPACE_S " \t"
#define WHITESPACE_C ' '
#define NULL_C '\0'

char *strstr(char *str1, char *str2);
size_t strlen(char *str);
char *bgets(char delim);

int main() {
    printf("Enter string:\n");
    char *string = bgets(NEWLINE_C);
    printf("Enter substring to search for:\n");
    char *substring = bgets(NEWLINE_C);
    printf("String starting from first occurrence of substring:\n%s\n", strstr(string, substring));
    free(string);
    free(substring);
    return 0;
}

char *strstr(char *str1, char *str2) {
    if (!*str2) return str1;
    size_t len1 = strlen(str1), len2 = strlen(str2), i, j;
    for (i = 0; i < len1; ++i) {
        for (j = 0; j < len2; ++j) {
            if (str1[i+j] != str2[j]) break;
            if (!str2[j+1]) return str1 + i;
        }
    }
    return NULL;
}

size_t strlen(char *str) {
    size_t len = 0;
    while (str[len]) ++len;
    return len;
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
