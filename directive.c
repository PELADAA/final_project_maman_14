#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "AsData.c"
#include "Symbols.c"
#include "Actions.c"
#include "utils.c"
#include "orders.c"

char* directives[5] = { "data\0", "string\0", "struct\0", "entry\0", "extern\0" };

int isItDirective(char* input_node_head->arr, int arrSpotCounter)
{
    int iterator = 1;
    char directive[7];
    int i;
    if (command[arrSpotCounter] == '.')
    {
        while ((input_node_head->arr[arrSpotCounter + iterator] != ' ') && (input_node_head->arr[arrSpotCounter + iterator] != '\t') && (input_node_head->arr[arrSpotCounter + iterator] != '\0'))
        {
            if (iterator >= 7)
                return -1;
            directive[iterator - 1] = input_node_head->arr[arrSpotCounter + iterator];
            iterator++;
        }
        directive[iterator - 1] = '\0';
        for (i = 0; i < 5; i++)
        {
            if (strcmp(directive, directives[i]) == 0)
            {
                return i + 1;
            }
        }
        return -1;

    }
    return -1;
}
