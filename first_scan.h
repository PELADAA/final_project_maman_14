#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "utils.h"



#ifndef commanSize
#define commanSize 81
#endif

#ifndef mask
#define mask 1
#endif



int binToDecimal(char* bin);                        /* Receives an array of chars holding a number in its binary form, and returns the number in decimal*/
char* decimalToBin(int num);                       /* Receives a number and returns an array holding the number in binary form */
char* binToMozar(char* bin);                        /* Receives a char array holding a number in binary, and returns an array holding the number in the special 32 base */
char* decimalToMozar(int num);                     /* Receives a number, and returns an array holding the number in the special 32 base */
char* concat(const char* s1, const char* s2);       /* input: two strings.  Output: one string that is the combination of both strings*/
int textToNum(char* text, int from, int end);       /* Input: Receives a string and integer 'from', and integer 'end'.  Output: A number that is a substring of this string from 'from' to 'end'*/




/* TODO refactor*/
char* getCommand(FILE*);/*Input: pointer to file. Output: char[81] that in the end of comman: /0. Discounts: file is open for reading*/
char getNext(FILE*);/*Input: pointer to file. Output: next char. Discounts: file is open for reading*/
void setNext(char c);/*Input: pointer to file, and next char.*/
int jumpSpace(char* command, int from);/*Input: pointer to arry, and starting poin. Output: point after starting text. Discounts: (1)*/
int jumpBreak(char* command, int from);/*Input: pointer to arry, and starting poin. Output: point after comma. Discounts: (1)*/
int isTextLeft(char* command, int from);/*Input: pointer to arry, and starting poin. Output: if there is text left? 1 : 0. Discounts: (1)*/
int endOfText(char* command, int from);/*Input: pointer to arry, and starting poin. Output: point of end of text (comma, apostrophes or space). Discounts: (1)*/

/* TODO refactor*/
typedef struct nodeSymbol* ptSymbol;
typedef struct nodeSymbol { char* name; int adress;/*in decimal*/ short type;/*0,1,2 or 3*/ ptSymbol next; }nodeSymbol;

int SetNext(ptSymbol* head, char* command, int from, int length, int adress, short type);/*Input: all data needed for new symbol, and head of list. Action: add symbol to list. Discounts: all data is corect. Output: 1 if saccsess, or number<0 otherwise.*/
int checkExist(ptSymbol head, char* name);/*Input: head of list and name to check existient. Output: 1 if exist 0 else.*/
ptSymbol GetIfExist(ptSymbol head, char* name);/*Input: head of list and name to check existient. Output: pointer to node if exist, or NULL else.*/
int isSYEmpty(ptSymbol head);/*Input: head of list. Output: 1 if empty, 0 else.*/
ptSymbol getNextSY(ptSymbol* head);/*Input: head of List. Output: head of list add delete from list.*/
void DeleteSymbols(ptSymbol* head);/*Input: head of List. Output: delete all list*/
int addSymbols(ptSymbol* head, char* command, int from);/*Input: head of list, command and where to start from. Output: adding all Symbol to extern*/
void upgreadeSymbols(ptSymbol head, int IC);/*Input: head of list and IC. Output: updating all symbols adress.*/
/*^ TODO refactor ^*/

void first_scan(node_t* input_node_head);