#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "constants.h"
#include "structs.h"

//#define SPACE 32
#define MAX 100


struct Macro {
    char mname[MAX];
    char mcontent[MAX];
    struct Macro* next;
};
void addToMtable(struct Macro* head, char name[], char content[]);
void printMacroTable(struct Macro* tail);
int IsMacroOrEndm(char line[]);
void InsertName(struct Macro* temp, char line[]);
void InsertContent(struct Macro* temp, FILE* fp);
int PreReadFile(int i, char* argv[], struct Macro* head);
int IsMacroCall(char line[], FILE* fpw, struct Macro* tail);
void PreWriteFile(int i, char* argv[], struct Macro* tail);

void printlist(node_t* head);
node_t* insert_at_head(node_t** head, node_t* node_to_insert);
node_t* find_node(node_t* head, int value);
char* clear_spaces(char input_str[]);
node_t* create_new_node(int value);
void insert_after_node(node_t* node_to_insert_after, node_t* newnode);
//int check_for_macro(FILE* file_to_read);


char temp_str[80];
char* macro_name[80];
