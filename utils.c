#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "AsData.c"
#include "Symbols.c"
#include "directive.c"
#include "Actions.c"
#include "orders.c"

int checkMortTxt(char* arrLine, int from)
{
    char c;
    while (arrLine[from] != '\0' && isspace( arrLine[from]))
        from++;
    return (arrLine[from] != '\0') ? 1 : 0;
}

int isItNumber(char* arrLine, int from)
{
	int start = from, end = 0;
	if (start + end < 81 && (arrLine[start + end] == '-' || arrLine[start + end] == '+'))
		start++;
	while (arrLine[start + end] != '\0' && arrLine[start + end] >= '0' && arrLine[start + end] <= '9') {
		end++;
	}
	return (end == 0) ? -1 : start + end;
}

char* entryToEAE(char* arrLine, int from, int end)
{
	static char name[30];
	symbolPtr temp = Head_Symbol;
	int lengthOfN = end - from + 1, i, result;
	for (i = 0; i < lengthOfN; i++)
	{
		name[i] = arrLine[from + i];
	}
	name[i] = '\0';
	while (temp)
	{
		if (strcmp(temp->name, name) == 0)
		{
			if (temp->type == 2)
				return "`Syntax error, entery Symbol can't be external one.\0";
			result = addEAE(&Head_EAE, temp->name, temp->adress, 0);
			if (result == -2)
				return "`Syntax error, Error in dynamic alocation.\0";
			else
				return NULL;
		}
		temp = temp->next;
	}
	return "`Syntax error, Symbol dosn't exist in hole file.\0";
}
