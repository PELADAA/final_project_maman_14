#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "AsData.c"
#include "Symbols.c"
#include "directive.c"
#include "Actions.c"
#include "utils.c"
#include "orders.c"
#define ErrorJump \
continue;





dataPointer HeadOfAsData = NULL; // datapoiters defenition is in AsData.c

void first_scan(node_t* input_node_head) {
    char symNameTmp[81];//symbol max size
    int IC = 100;
    int DC = 0, L = 0;
    int lineCounter = 0;
    int directiveType, Nresult;
    int symbol_flag = 0;
    char* ptr;
    symbolPtr* symbolnode;
    symbolPtr* symbol_head = NULL;
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
                printf("comment found\n");
                IC--;
          }
         else if (strstr(ptr, ":") != NULL) {
                symbol_flag = 1;
                ptr = input_node_head->arr;
                char c = *ptr;
                int SYMrunning_counter;

                for (SYMrunning_counter = 0; c != LABEL_DELIM; SYMrunning_counter++) {
                    //printf("%c", c);
                    c = (char)*(ptr++);
                    arrSpotCounter++;
                    symNameTmp[SYMrunning_counter] = c;
                    if (c == SPACE)
                        running_counter--;
                }
                symNameTmp[running_counter + 1] = '\0';
         }
        if (running_counter > 0)
        {
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
                arrSpotCounter++
                    while ((input_node_head->arr[arrSpotCounter]) != '\0' && isspace(input_node_head->arr[arrSpotCounter]))//
                        arrSpotCounter++;
                if (!checkMortTxt(input_node_head->arr, arrSpotCounter))
                {
                    printf("Error: in (line: %d, index: %d) Syntax error, expected a method name or directive after symbol.\n");
                    //ErrorJump
                }
            }
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
               if (symbol_flag == 1) 
               {
                symbol_flag = 0;
                  if (checkSymbolExist(symbol_head, symNameTmp)) 
                  {
                   printf(" Symbol already exist, and have been defined befor.\n");
                   //ErrorJump
                  }
                  if (directiveType == 3)
                  directiveType = SetNextS(&symbol_head, input_node_head->arr, symNameTmp, DC, 1);//1- for sruct.
                  else
                  directiveType = SetNextS(&symbol_head, input_node_head->arr, symNameTmp, DC, 0);
                  if (directiveType == -2)
                  {
                   printf("Dynamic alocation error, could not add Symbol.\n");
                   ErrorJump
                  }

               }
               switch (directiveType)
               {
                            case 1: //adding data from the .data to the data list
                                directiveType = addDataN(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
                                if (directiveType < 0 && directiveType != -2)
                                {
                                    printf("Error: in (line: %d, index: %d) Syntax error, after directive name. (expected: number,number..) note: all number must be between: -512:512 .\n", lineNumber, index);
                                    ErrorJump
                                }
                                break;
                            case 2://adding data from the .struct to the data list
                                directiveType = addStructNS(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
                                if (directiveType < 0 && directiveType != -2)
                                {
                                    printf("Error: in (line: %d, index: %d) Syntax error, after directive name. (expected: \"sum_text\").\n", lineNumber, index);
                                    ErrorJump
                                }
                                break;
                            case 3:	//adding data from the .string to the data list	
                                directiveType = addString(input_node_head->arr, arrSpotCounter, &DC, &HeadOfAsData);
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
                            
               if (checkMortTxt(input_node_head->arr, arrSpotCounter))
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
                   if (checkMortTxt(input_node_head->arr, arrSpotCounter))
                   {
                       
                       while (input_node_head->arr[arrSpotCounter]) != '\0' && isspace(input_node_head->arr[arrSpotCounter]))
                          arrSpotCounter++;
                       directiveType = addMSymbols(&symbol_head, input_node_head->arr, arrSpotCounter);
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
        if (symbol_flag == 1)
        {
          symbol_flag = 0;
          if (checkSymbolExist(symbol_head, symNameTmp)
          {
           printf("Error/ in (line: %d, index: %d) Syntax error, Symbol already exist, and have been defined befor.\n", lineNumber, Sy_start);
           ErrorJump
           }
           //directiveType now it has other input than directive
           directiveType = SetNextS(&symbol_head, input_node_head->arr, symNameTmp, IC, 3);/*3- for code Symbol.*/
           if (directiveType == -2)
           {
             printf("Error: in (line: %d, index: %d) Dynamic alocation error, could not add Symbol.\n", lineNumber, Sy_start);
             ErrorJump
           }
        }
                //directiveType now it has other input than directive
        directiveType = isItOrder(input_node_head->arr, arrSpotCounter);
         if (directiveType < 0)
         {
            printf("Error: in (line: %d, index: %d) Syntax error, unknow order name.\n", lineNumber, index);
            ErrorJump
         }
         TResult = countActionList(directiveType, &L, input_node_head->arr, arrSpotCounter);
         if (TResult != NULL && TResult[0] == '`')
         {
             printf("Error: in (line: %d, index: %d) %s.\n", lineCounter, arrSpotCounter, (TResult + 1));
             ErrorJump
         }
                
      IC += L;
                
    }
    upgradeSymbols(symbol_head, IC);
}

