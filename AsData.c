#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "macro_deploy.h"
#include "Symbols.c"
#include "directive.c"
#include "Actions.c"
#include "utils.c"
#include "orders.c"
#include "txtTranslation.c"



char* directives[5] = { "data\0","string\0","struct\0","entry\0","extern\0" };


typedef struct dataList* dataPointer;
typedef struct dataList {
    int data; /* in decimal */
    int DC; /*in decimal*/
    dataPointer next;

} dataList;

/*(1) returns 1 if all worked well, -2 if there was a dynamic allocation error and -1 otherwise*/

int addNode(dataPointer* head, int number, int* DC);
int addString(char* command, int from, int* DC, dataPointer* head);
int addStructNS(char* command, int from, int* DC, dataPointer* head);
int addDataN(char* command, int from, int* DC, dataPointer* head);
void deleteDataList(dataPointer* head);
void printDataList(dataPointer head);
                                                                                       
 /*adds the number in command that is represented as a string from index 'iterator' to index 'endNum'. returns (1) above.*/

int addNumber(char * command, int iterator, int endNum, int *DC, dataPointer * head){
    int newNumber = textToNum(command,iterator,endNum);        
    int added;
    if(newNumber>512 || newNumber<-512)
        return -1;
    if ((added = addNode(head, newNumber, DC) < 0))
        return added;
    return 1;
}
/*Input: a pointer to a pointer to a dataList structure, a number which is the data and a pointer to DC
  *Output: (1) above
 *Action: First, it creates a new dataList structure which contains the inputted number and DC, then if there is a linked list which the inputted dataList structure as its head, it adds it to the end of the list, otherwise the function sets it to be the head of the list. The function also adds 1 to the given DC*/

int addNode(dataPointer *head , int number, int *DC){
    dataPointer newData = (dataPointer)malloc(sizeof(dataList));
    dataPointer temp;
    if(newData == NULL){
        return -2;
    }
    newData->data=number;
    newData->DC=*DC;
    newData->next=NULL;
    *DC+=1;
    if(*head==NULL){
        *head=newData;
        return 1;
    }

    temp=*head;
    while(temp->next!=NULL){
        temp=temp->next;
    }
    temp->next=newData;
    return 1;

}


/*Input: a string which contains a string (with quotations), an integer that represents the starting point, a pointer to DC, and a pointer to the head of the list
  *Output: If the string was successfully added to the dataList, the function returns the position after the second quotations, else -2 if there was a dynamic allocation error and -1 otherwise
  * Action: The functions adds every letter to the dataList structure, including the '\0' character*/

int addString(char* command, int arrSpotCounter, int* DC, dataPointer* HeadOfAsData) {
    int iterator = from + 7;
    while (command[iterator]) != '\0' && isspace(command[iterator])){
    iterator++; }
    return addStringThatIsNotADirective(command, iterator, head, DC);
}

    int addStringThatIsNotADirective(char* command, int from, dataPointer * head, int* DC) {
        int iterator = from;
        int added;
        if (command[iterator] != '\"')
            return -1;
        iterator++;
        while (command[iterator] != '\"' && checkMortTxt(command, iterator)) {
            if ((added = addNode(head, command[iterator], DC)) < 0)
                return added;
            iterator++;
        }
        if (command[iterator] != '\"')
            return -1;
        if ((added = addNode(head, '\0', DC)) < 0)
            return added;
        return iterator + 1;
    }
    
}
/*Input: a string which represents a struct directive, an integer from, a pointer to DC and a pointer to the head of the dataList
  *Output: if successful in adding the struct, it returns the index after all parameters. else, it returns -2 if there was a dynamic allocation error and -1 otherwise
  *Action: First it adds the number to the dataList, and then it adds each letter of the string to the dataList, including '\0'*/

int addStructNS(char *command, int arrSpotCounter, int *DC, dataPointer * HeadOfAsData) {
    int iterator = from+7;
    int endNum;
    int num;
    int endStruct;    
    while (command[iterator]) != '\0' && isspace(command[iterator])){
    iterator++; }
    if ((endNum = isItNumber(command, iterator)) < 0) {
        return -1;
    }    
    num = addNumber(command,iterator,endNum-1,DC,head);
    if(num<0)
        return num;
    iterator=endNum;
    while (command[iterator]) != '\0' && isspace(command[iterator])){
    iterator++; }
    if(command[iterator]!=',')
        return -1;
    iterator += 1;
    while (command[iterator]) != '\0' && isspace(command[iterator])){
    iterator++; }
    if(command[iterator]!='\"')
        return -1;
    if((endStruct=addStringThatIsNotADirective(command,iterator,head,DC))<0)
        return endStruct;    
    return endStruct;
}
/*Input: Input: a string which represents a data directive, an integer from, a pointer to DC and a pointer to the head of the dataList
 *Output: if all the numbers have been added successfully, than the function returns the index after all the numbers, else return -2 if there was a dynamic allocation error and -1 otherwise.
 * Action: adds all the numbers provided in the .data directive to the dataList*/

int addDataN(char *command, int arrSpotCounter, int *DC, dataPointer * HeadOfAsData){
    int iterator=from+5;
    int endNum;
    int number;    
    while (command[iterator]) != '\0' && isspace(command[iterator])){
    iterator++; }
    if(!checkMortTxt(command,iterator))
        return -1;
    if((endNum = isItNumber(command,iterator))<0)
        return endNum;    

    number=addNumber(command,iterator,endNum-1,DC,head);
    if(number<0)
        return number;
    iterator=endNum;    
    while(checkMortTxt(command,iterator)) {
        while (command[iterator]) != '\0' && isspace(command[iterator])){
        iterator++; }
        if(command[iterator]!=',')
             return iterator;
        iterator++;
        while (command[iterator]) != '\0' && isspace(command[iterator])){
        iterator++; }
        if((endNum = isNumber(command,iterator))<0)
            return endNum;        
        number=addNumber(command,iterator,endNum-1,DC,head);
        if(number<0)
            return number;
        iterator=endNum;        
    }
    return iterator;
}
/*Input: a pointer to the head of the dataList
  *Output: none
  * Action: frees the dataList*/

void deleteDataList(dataPointer * head){    
    dataPointer pt,temp;
    temp = *head;
    while(temp)
    {
        pt = temp->next;        
        free(temp);
        temp = pt;
    }
    *head = NULL;
}
/*prints the list*/
void printDataList(dataPointer head){
    dataPointer temp = head;
    while(temp){
        printf("(%d,%d)\n",temp->data,temp->DC);
        temp=temp->next;
    }
}
