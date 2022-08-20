
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "macro_deploy.h"
# include "AsData.c"
# include "Symbols.c"
# include "directive.c"
# include "utils.c"
# include "orders.c"
char* countActionList(int actionNum, int* L, char* input_node_head->arr, int arrSpotCounter)
{
	int lineCount = 1, firstAddress, secondAddress; /*1 for first word command*/
	from += 3;
	if (actionNum >= 14)
	{
		if (actionNum == 15)
			from += 2;
		if (checkMortTxt(input_node_head->arr, arrSpotCounter))
		{
			return "`Syntax error, unexpected text afer action name.\0";
	}
	else/*needed at least one operste*/
	{
		if (!checkMortTxt(input_node_head->arr, arrSpotCounter))
			return "`Syntax error, expected operate after action name.\0";
		while ((ch = input_node_head->arr[arrSpotCounter]) != '\0' && !isspace(ch) && (ch != ','))
		 arrSpotCounter++;
		firstAddress = getNAddressing(input_node_head->arr, arrSpotCounter);
		switch (firstAddress)
		{
			case 0:
				if (actionNum <= 3 || actionNum == 12)
						lineCount += 1;
				else
					return "`Syntax error, Addressing number: 0, can't be in first addressing at this action.\0";
				break;
			case 1:
					lineCount += 1;
				break;
			case 2:
					lineCount += 2;
				break;
			case 3:
				if (actionNum != 6)
						lineCount += 1;
				else
					return "`Syntax error, Addressing number: 3, can't be in first addressing at this action.\0";
				break;
		}
		char ch;
		while ((ch = input_node_head->arr[arrSpotCounter]) != '\0' && !isspace(ch) && (ch != ','))
		arrSpotCounter++;
		if (actionNum <= 3 || actionNum == 6)
		{
				//jumpbreak:
			while ((input_node_head->arr[arrSpotCounter]) != '\0' && isspace(input_node_head->arr[arrSpotCounter]))
				arrSpotCounter++;
			if (input_node_head->arr[arrSpotCounter] == ',')
			{
					arrSpotCounter ++;
			}
			else
			{
				arrSpotCounter = -1;
			}
			if (arrSpotCounter == -1)
				return "`Syntax error, expected a break ',' and another command in this action.\0";
			while ((input_node_head->arr[arrSpotCounter]) != '\0' && isspace(input_node_head->arr[arrSpotCounter]))
				arrSpotCounter++;
			secondAddress = getNAddressing(input_node_head->arr, arrSpotCounter);
			switch (secondAddress)
			{
				case 0:
				if (actionNum == 1)
					lineCount += 1;
				else
					return "`Syntax error, Addressing number: 0, can't be in second addressing at this action.\0";
				break;
				case 1:
				lineCount += 1;
				break;
				case 2:
				lineCount += 2;
				break;
				case 3:
				lineCount += (firstAddress == 3) ? 0 : 1;
				break;
			}
		}
		else
		{
				if (checkMortTxt(input_node_head->arr, arrSpotCounter))
					return "`Syntax error, unexpected text, after operate.\0";
		}
	}
	*L = lineCount;
	return NULL;
}


	int getNAddressing(char* input_node_head->arr, int arrSpotCounter)
	{
		int i = 0;
		if (input_node_head->arr[arrSpotCounter] == '#')
			return 0;
		if (input_node_head->arr[arrSpotCounter] == 'r' && input_node_head->arr[arrSpotCounter+1] >= '0' && input_node_head->arr[arrSpotCounter + 1] <= '7')
			return 3;
		while (input_node_head->arr[arrSpotCounter + i] != '\0' && !isspace(input_node_head->arr[arrSpotCounter + i]) && input_node_head->arr[arrSpotCounter + i] != '.' && input_node_head->arr[arrSpotCounter + i] != ',')
			i++;
		return (input_node_head->arr[arrSpotCounter + i] == '.') ? 2 : 1;
	}
