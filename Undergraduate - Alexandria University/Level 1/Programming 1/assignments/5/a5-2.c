/*
* Assignment 5
 * Solution to Problem 2
 * Author: Youssef Samy
 * License: BSD 3-Clause
 * Compilation Instructions
 * msvc: cl .\a5-2.c /std:c11           # produces a5-2.exe
 * gcc: gcc ./a5-2.c -std=c89           # produces a.out or a.exe
 * clang: clang ./a5-2.c -w --std=c11   # produces a.out or a.exe
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

char *bgets(char delim);
int checkPalindrome(char *word);
void detokenize(char *start_ptr, char* end_ptr, char delim);

int main() {
    printf("Enter a newline-terminated string:\n");
    char *input_string = bgets(NEWLINE_C), *end_ptr = NULL, *token = NULL;
    end_ptr = input_string + strlen(input_string);
    token = strtok(input_string, WHITESPACE_S);
    int min[2] = {}, max[2] = {}, palindrome_len;
    while (token != NULL) {
        palindrome_len = checkPalindrome(token);
        if (!palindrome_len) {
            token = strtok(NULL, WHITESPACE_S);
            continue;
        }
        if (max[0] < palindrome_len) {
            max[1] = token - input_string;
            max[0] = palindrome_len;
        }
        if (min[0] > palindrome_len || !min[0]) {
            min[1] = token - input_string;
            min[0] = palindrome_len;
        }
        token = strtok(NULL, WHITESPACE_S);
    }
    if (!max[0] || !min[0]) {
        printf("No palindrome\n");
    }
    else {
        printf("The largest palindrome was of size %d: %s\n", max[0], (input_string + max[1]));
        printf("The minimum palindrome was of size %d: %s\n", min[0], (input_string + min[1]));
    }
    detokenize(input_string, end_ptr, WHITESPACE_C);
    free(input_string);
    return 0;
}

int checkPalindrome(char *word) {
    int len = strlen(word), offset;
    for (offset = 0; offset < len / 2; ++offset) {
        if (word[offset] != word[len - offset - 1]) return 0;
    }
    return len;
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
