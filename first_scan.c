#include "first_scan.h"
#include "macro_deploy.h"
#include "AsData.c"
#include "Symbols.cs"
#include "directive.cs"
#include "Actions.cs"
#include "utils.c"
#include "orders.cs"

char symbolName[81];



char symNameTmp[81];//symbol max size

dataPointer HeadOfAsData = NULL; // datapoiters defenition is in AsData.c

node_t* first_scan(node_t* input_node_head) {
    int IC = 100;
    int DC = 0, L = 0;
    int lineCounter = 0;
    int directiveType, Nresult;
    int symbol_flag = 0;
    char* ptr;
    node_t* symbolnode;
    node_t* symbol_head = NULL;
    printf("input_node_head: %d\n", IC);
    /* Rewind input list */
    while (input_node_head->next != NULL) {
        input_node_head = input_node_head->next;
    }


    while (input_node_head->prev != NULL) {
        //printf("IC: %d\n", IC);
        input_node_head = input_node_head->prev;
        ptr = input_node_head->arr;
        int arrSpotCounter = 0;
        lineCounter++;
        char* TResult = NULL
            if (strstr(ptr, ";") != NULL) {
                //printf("comment found, ptr: %c\n", *ptr);
                IC--;
            }
            else if (strstr(ptr, ":") != NULL) {
                symbol_flag = 1;
                ptr = input_node_head->arr;
                char c = *ptr;
                int running_counter;

                for (running_counter = 0; c != LABEL_DELIM; running_counter++) {
                    //printf("%c", c);
                    c = (char)*(ptr++);
                    arrSpotCounter++;
                    symNameTmp[running_counter] = c;
                    if (c == SPACE)
                        running_counter--;
                }
                symNameTmp[running_counter + 1] = '\0';

                //checks if the label already excist  - if yes error
                if (checkSymbolExist(symbol_head, symNameTmp))
                {
                    printf("Error: Symbol already exist, and have been defined befor.\n");
                    ErrorJump
                }
                else
                {
                    if (running_counter > 30)
                    {
                        printf(" Syntax error, Symbol name can't be longer than: 30.\n");
                        //ErrorJump
                    }
                    //check - if heres something after the symbol. 
                    //  check what error needs to be if its infinity loop 
                    while (input_node_head->arr[arrSpotCounter] == '\0' && isspace(input_node_head->arr[arrSpotCounter]))
                    {
                        arrSpotCounter++;
                    }
                    if (input_node_head->arr[arrSpotCounter] == '\0')
                    {
                        printf("Error: in (line: %d, index: %d) Syntax error, expected a method name or directive after symbol.\n");
                        //ErrorJump
                    }
                    if (input_node_head->arr[arrSpotCounter] == '.')
                    {

                        directiveType = isItDirective(input_node_head->arr, arrSpotCounter);
                        if (directiveType <= 0)
                        {
                            printf("Error: Syntax error, unknow directive name.\n");
                            //ErrorJump
                        }

                        if (directiveType <= 3)  //directive after symbol- how to set next symbol?
                        {
                            if (symbol_flag == 1) {

                                symbol_flag = 0;
                                if (checkSymbolExist(symbol_head, symNameTmp)) {
                                    printf(" Symbol already exist, and have been defined befor.\n");
                                    //ErrorJump
                                }
                                if (directiveType == 3)
                                    directiveType = SetNext(&symbol_head, input_node_head->arr, symbolName, DC, 1);//1- for sruct.
                                else
                                    directiveType = SetNext(&symbol_head, input_node_head->arr, symbolName, DC, 0);
                                if (directiveType == -2)
                                {
                                    printf("Dynamic alocation error, could not add Symbol.\n");
                                    //ErrorJump
                                }

                            }
                            switch (directiveType)
                            {
                            case 1: //adding data from the .data to the data list
                                directiveType = addData(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
                                if (directiveType < 0 && directiveType != -2)
                                {
                                    printf("Error: in (line: %d, index: %d) Syntax error, after directive name. (expected: number,number..) note: all number must be between: -512:512 .\n", lineNumber, index);
                                    ErrorJump
                                }
                                break;
                            case 2://adding data from the .string to the data list
                                directiveType = addString(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
                                if (directiveType < 0 && directiveType != -2)
                                {
                                    printf("Error: in (line: %d, index: %d) Syntax error, after directive name. (expected: \"sum_text\").\n", lineNumber, index);
                                    ErrorJump
                                }
                                break;
                            case 3:	//adding data from the .struct to the data list				
                                directiveType = addStruct(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
                                if (directiveType < 0 && directiveType != -2)
                                {
                                    printf("Error: in (line: %d, index: %d) Syntax error, after directive name. (expected: number,\"sum_text\").\n", lineNumber, index);
                                    ErrorJump
                                }
                                break;
                            }
                            if (directiveType == -2)
                            {
                                printf("Error: Dynamic alocation error, could not add data.\n");
                                //ErrorJump
                            }
                            while ((input_node_head->arr[arrSpotCounter)]) != '\0' && isspace(input_node_head->arr[arrSpotCounter))){
                            arrSpotCounter++; }
                            if (input_node_head->arr[arrSpotCounter] != '\0')
                            {
                                printf("Error: in (line: %d, index: %d) Syntax error, unexpected text after directive order.\n", lineNumber, directiveType);
                                ErrorJump
                            }
                        }
                        else
                        {
                            if (symbol_flag == 1)
                            {
                                symbol_flag = 0;
                                printf("Warning in (line: %d, index: %d) unexpected Symbol in this type of directive.\n", lineNumber, /*Sy_start*/);
                            }
                            if (directiveType == 5)
                            {
                                arrSpotCounter += 7;
                                while ((input_node_head->arr[arrSpotCounter)]) == '\0' && isspace(input_node_head->arr[arrSpotCounter))){
                                arrSpotCounter++; }
                                if (input_node_head->arr[arrSpotCounter] != '\0')
                                {
                                    //replace jump space
                                    arrSpotCounter = jumpSpace(input_node_head->arr, arrSpotCounter);
                                    //understand what is addSymbols
                                    directiveType = addSymbols(&symbol_head, input_node_head->arr, arrSpotCounter);
                                    if (directiveType < 0)
                                    {
                                        switch (directiveType)
                                        {
                                        case -2:
                                            printf("Error: in (line: %d, index: %d) Dynamic alocation error, could not add Symbol.\n", lineNumber,/*Sy_start*/);
                                            ErrorJump
                                                break;
                                        case -3:
                                            printf("Error: in (line: %d, index: %d) Syntax error, unexpected text after adding symbols.\n", lineNumber, arrSpotCounter);
                                            ErrorJump
                                                break;
                                        default:
                                            printf("Error: in (line: %d, index: %d) Syntax error, expected symbol name.\n", lineNumber, arrSpotCounter);
                                            ErrorJump
                                        }
                                    }
                                }
                                else
                                {
                                    printf("Error: in (line: %d, index: %d) expected symbol name afted directive: extern.\n", lineNumber, /*Sy_start*/);
                                    ErrorJump
                                }
                            }
                        }
                        
                        continue;
                    }
                }
                if (symbol_flag == 1)
                {
                    symbol_flag = 0;
                    if (checkSymbolExist(symbol_head, symNameTmp)
                    {
                        printf("Error/ in (line: %d, index: %d) Syntax error, Symbol already exist, and have been defined befor.\n", lineNumber, Sy_start);
                            //ErrorJump
                    }
                    //directiveType now it has other input than directive
                    directiveType = SetNext(&symbol_head, input_node_head->arr, symbolName, IC, 3);/*3- for code Symbol.*/
                        if (directiveType == -2)
                        {
                            printf("Error: in (line: %d, index: %d) Dynamic alocation error, could not add Symbol.\n", lineNumber, Sy_start);
                                //ErrorJump
                        }
                }
                //directiveType now it has other input than directive
                directiveType = isItOrder(input_node_head->arr, arrSpotCounter);
                if (directiveType < 0)
                {
                    printf("Error: in (line: %d, index: %d) Syntax error, unknow order name.\n", lineNumber, index);
                    //ErrorJump
                }
                TResult = countActionList(directiveType, &L, input_node_head->arr, arrSpotCounter);
                if (TResult != NULL && TResult[0] == '`')
                {
                    printf("Error: in (line: %d, index: %d) %s.\n", lineCounter, arrSpotCounter, (TResult + 1));
                    //ErrorJump
                }
                
                IC += L;
                
            }
        //what this line does?
        upgreadeSymbol(symbol_head, IC);
    }

}


        //printf("ptr location is: %s\n", ptr);


        // define 
        //TODO check for labels serch for ":" and return "label exist"
        // if ":" exist => set label exist to "1"
        // return the pointer to start of the line
        //jumpspace || 
        //while isalphanumeric || isnumber  copy char to struct_symbl.label_name 


        //TODO create node 


        //if exist, return to the start of the line, skip spaces and copy the labal name

        //store the label name with the counter in the simbol stack


        //after symbol table is created

        //check for "."

        /*Lada:first check
            -loop that goes over each line at file
            -operands: ץ raise notice for a symbol, number of line
            A check if there’s no empty spots or next line.
            - -good line: finds num of the first char after space (the number of the char in the line)
            - -Find number of the last char in the word
            - -A check if there’s a really a label(:)
            - -Pointer to the begging of the label+ length of the label to check if it’s length ok
            - -A check if there’s something after the label (needs to be else error)
            - -Checks if after label comes directive + is valid and existent directive
            - If a struct -add the label to the list (set next) short type for struct=1 (others 0)
            - -Now adding the data after string ,data ,or struct directive to data list and returns the index after this data
            - -Checks if there’s something left in the. Line (not supposed to be
            - -Check if directive is .extern
            - -Moves index after the” .extern” and adds data(label) to the list
            - -If there’s no directive, checks if there’s previous label- if no then adds label to list
            - -Than looks if there’s an order and returns number of order
            - -Checks and returns how many location spots the order needs
            - -Updating the location spots in IC
            - -In the end of the file- command that updating all labels address */
        IC++;
    }
    printf("symbole list:\n");


    if (symbol_flag == 1) {
        printlist(symbol_head);
        printf("head is  null? %p\n", symbol_head);
        return symbol_head;
    }
    else {
        printf("head is %p\n", symbol_head);
        return NULL;
    }
}


