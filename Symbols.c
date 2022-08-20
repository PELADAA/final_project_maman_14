#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "AsData.c"
#include "directive.c"
#include "Actions.c"
#include "utils.c"
#include "orders.c"

typedef struct nodeSymbol *symbolPtr;
typedef struct nodeSymbol { char* name; int adress;/*in decimal*/ short type;/*0,1,2 or 3*/ symbolPtr next; }nodeSymbol;

void upgradeSymbols(symbolPtr symbol_head, int IC)
{
    while (symbol_head)
    {
        if (symbol_head->type <= 1)
            symbol_head->adress += IC;
        symbol_head = symbol_head->next;
    }
}

int SetNextS(symbolPtr* symbol_head, char* input_node_head->arr, char* symNameTmp, int adress, short type)
{
    symbolPtr pt;
    if (*symbol_head)
    {
        pt = *symbol_head;
        while (pt->next)
        {
            pt = pt->next;
        }
        pt->next = (ptSymbol)malloc(sizeof(nodeSymbol));
        pt = pt->next;
    }
    else
    {
        *symbol_head = (ptSymbol)malloc(sizeof(nodeSymbol));
        pt = *symbol_head;
    }
    if (pt && (pt->name = (char*)malloc((length + 1) * sizeof(char))))
    {
        pt->next = NULL;
        pt->name = strncpy(pt->name, symNameTmp);
        pt->name[length] = '\0';
        pt->adress = adress;//excists in node_t?
        pt->type = type;//excists in node_t?
    }
    else
    {
        return -2;
    }
    return 1;
}


int checkSymbolExist(symbolPtr* symbol_head, char* symNameTmp)//is it called ptSymbol inour project?
{
    while (symbol_head)
    {
        if (strcmp(symbol_head->name, symNameTmp) == 0)
            return 1;
        symbol_head = symbol_head->next;
    }
    return 0;
}

ptSymbol GetSIfExist(symbolPtr symbol_head, char* symNameTmp)
{
    while (symbol_head)
    {
        if (strcmp(symbol_head->name, symNameTmp) == 0)
            return symbol_head;
        symbol_head = symbol_head->next;
    }
    return NULL;
}

int isSYEmpty(symbolPtr symbol_head)
{
    return (symbol_head) ? 0 : 1;
}

ptSymbol getNextS(symbolPtr* symbol_head)
{
    ptSymbol p;
    if (!isSYEmpty(*symbol_head))
    {
        p = *head;
        *head = (*symbol_head)->next;
        return p;
    }
    return NULL;
}

void DeleteSy(symbolPtr* symbol_head)
{
    node_t pt, next;
    if (!isSYEmpty(*symbol_head))
    {
        pt = *symbol_head;
        while (pt)
        {
            next = pt->next;
            free(pt->name);
            free(pt);
            pt = next;
        }
        *symbol_head = NULL;
    }
}

int addMSymbols(symbolPtr* symbol_head, char* input_node_head->arr, int from)
{
    int start, end, count = 0;
    int use = 0;
    while (checkMortTxt(input_node_head->arr, from) && from >= 0)
    {
        use = from;
        while (input_node_head->arr[use] != '\0' && isspace(input_node_head->arr[use])
            use++;
        start = use;
        while (input_node_head->arr[start] != '\0' && !isspace(input_node_head->arr[start]) && (input_node_head->arr[start] != ','))
            start++;
        end = start;
        if (end > -1)
        {
            if (SetNext(symbol_head, command, start, end - start, 0, 2) < 0)
                return -2;
            count++;
            while (input_node_head->arr[end] != '\0' && isspace(input_node_head->arr[end])
                    end++;
            from = end;
            if ((from == -1 && isTextLeft(input_node_head->arr, end)) || (from != -1 && !isTextLeft(input_node_head->arr, from)))
                return -3;
        }
        else
        {
            return -1;
        }
    }

    return count;
}
