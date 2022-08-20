#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "AsData.c"
#include "Symbols.cs"
#include "directive.cs"
#include "Actions.cs"
#include "utils.c"

char* orders[16] = { "mov\0", "cmp\0", "add\0", "sub\0", "not\0", "clr\0", "lea\0", "inc\0", "dec\0", "jmp\0", "bne\0", "red\0", "prn\0", "jsr\0", "rts\0", "stop\0" };
int isItOrder(char* input_node_head->arr, int arrSpotCounter)
{
    int iterator = 0;
    char order[5];
    int i;
    while (iterator < 4 && input_node_head->arr[arrSpotCounter + iterator] != '\0' && !isspace(input_node_head->arr[arrSpotCounter + iterator]))
    {
        order[iterator] = input_node_head->arr[arrSpotCounter + iterator];
        iterator++;
    }
    order[iterator] = '\0';
    for (i = 0; i < 16; i++)
    {
        if (strcmp(order, orders[i]) == 0)
        {
            return i;
        }
    }
    return -1;
}
