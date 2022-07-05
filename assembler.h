#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_MAX 80 
#define SPACE 32
#define TAB 11
#define NEW_LINE 10
#define END '\0'
#define ASTERISK '*'
#define DOT '.'
#define AS_SUFFIX ".as"
#define SUFFIX_LENGTH 5
#define BUFFER_MAX 80


struct  node
{
    char arr[LINE_MAX];
    int value;
    struct node* next;
};
typedef struct node node_t;