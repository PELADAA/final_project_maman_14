
#include "second_scan.h"

char* directives[5] = { "data\0","string\0","struct\0","entry\0","extern\0" };
char* orders[16] = { "mov\0","cmp\0","add\0","sub\0","not\0","clr\0","lea\0","inc\0","dec\0","jmp\0","bne\0","red\0","prn\0","jsr\0","rts\0","stop\0" };

int isSymbol(char* command, int from) {
    int iterator = 1;
    if (isalpha(command[from])) {
        while (isalpha(command[from + iterator]) || isdigit(command[from + iterator])) {
            if (iterator > 30) {
                return -1;
            }
            iterator++;
        }
        if (command[from + iterator] == ':')
            return from + iterator;
    }
    return -1;
}

int isDirective(char* command, int from) {
    int iterator = 1;
    char directive[7];
    int i;
    if (command[from] == '.') {
        while ((command[from + iterator] != ' ') && (command[from + iterator] != '\t') && (command[from + iterator] != '\0')) {
            if (iterator >= 7)
                return -1;
            directive[iterator - 1] = command[from + iterator];
            iterator++;
        }
        directive[iterator - 1] = '\0';
        for (i = 0;i < 5;i++) {
            if (strcmp(directive, directives[i]) == 0) {
                return i + 1;
            }
        }
        return -1;

    }
    return -1;
}
int isOrder(char* command, int from) {
    int iterator = 0;
    char order[5];
    int i;
    while (iterator < 4 && command[from + iterator] != '\0' && !isspace(command[from + iterator])) {
        order[iterator] = command[from + iterator];
        iterator++;
    }
    order[iterator] = '\0';
    for (i = 0;i < 16;i++) {
        if (strcmp(order, orders[i]) == 0) {
            return i;
        }
    }
    return -1;
}

int isNumber(char* command, int from)
{
    int start = from, end = 0;
    if (start + end < commanSize && (command[start + end] == '-' || command[start + end] == '+'))
        start++;
    while (command[start + end] != '\0' && command[start + end] >= '0' && command[start + end] <= '9') {
        end++;
    }
    return (end == 0) ? -1 : start + end;
}

node_t* second_scan(node_t* input_node_head) {

    node_t* temporary = input_node_head;
    int_structure temp_structure;
    //node_t* revers_temporary;
    //int i = 0;
    while (temporary->next != NULL) {/* go to the last element*/
        temporary = temporary->next;
    }
    while (temporary->prev != NULL) { /* print backwards */
        printf("%d - \t", temporary->value);
        printf("%s\t", temporary->arr);
        temporary = temporary->prev;
        // printf("is directive? %d\n", isDirective(temporary->arr, 0));
        // printf("is number? %d\n", isNumber(temporary->arr, 0));
        // printf("isOrder? %d\n", isOrder(temporary->arr, 0));
        // printf("isSymbol? %d\n", isSymbol(temporary->arr, 0));
    }


    printf("\n");

    return NULL;
}

node_t* second_scan_with_symbols(node_t* input_node_head, node_t* symbol_node_head) {

    node_t* temporary = input_node_head;
    FILE* first_scan_output = fopen("first_scan_output.txt", "w");
    int_structure temp_structure;
    temp_structure.opcode = 0;
    temp_structure.src_operand_ref = 0;
    temp_structure.dst_operand_ref = 0;
    temp_structure.a_r_e = 0;
    temp_structure.adress = 0;

    int input_index = 0, symbol_index = 0;
    int temp;
    while (temporary->next != NULL) {/* go to the last element*/
        temporary = temporary->next;
    }
    while (temporary->prev != NULL) { /* print backwards */
        // input_index = input_node_head->arr;
        // symbol_index = symbol_node_head->arr;
        temp_structure.adress = temporary->value;
        /*if (input_index = isSymbol(temporary->arr, input_index) > 0) {
            printf("Symbol found index=%d\n", input_index);
            //input_index = jumpSpace(temporary->arr, input_index);
            //printf("index=%d\n", input_index);
            // if (isOrder(temporary->arr, input_index) > 0) {
            //     printf("*****isOrder found after symbol\n");
            // }

        }*/
        //printf("arg test <%s>\n", orders[isOrder(temporary->arr, input_index)]);

        // if (isTextLeft(temporary->arr, input_index) == 1)
        //     printf("text is left\n");
        scanner_ptr = temporary->arr;
        input_index = jumpSpace(scanner_ptr, input_index);

        if (isOrder(scanner_ptr, input_index) >= 0) {
            printf("isOrder found <%s>\n", orders[isOrder(scanner_ptr, input_index)]);
            temp_structure.opcode = isOrder(scanner_ptr, input_index);
            if (isOrder(scanner_ptr, input_index) == 0) {
                scanner_ptr += (input_index + 3);
                printf("checking mov args in: \n%s> input_index: %d\n", scanner_ptr, input_index);
                //get 2 words

                printf("first arg: <%s>\n", strtok(scanner_ptr, ","));
                printf("next arg: <%s>\n", strtok(NULL, ","));

                //check if words are: #number | register | extern | LABEL

                //set the ref type

                //

            }
        }
        if (isDirective(temporary->arr, input_index) > 0) {
            printf("isDirective: %s found\n", directives[isDirective(temporary->arr, input_index)]);
        }
        if (isNumber(temporary->arr, input_index) > 0) {
            printf("isNumber found\n");
        }

        printf("%d - \t", temporary->value);
        printf("%s", temporary->arr);
        temporary = temporary->prev;
        // printf("is directive? %d\n", isDirective(temporary->arr, 0));
        // printf("is number? %d\n", isNumber(temporary->arr, 0));
        // printf("isOrder? %d\n", isOrder(temporary->arr, 0));
        // printf("isSymbol? %d\n", isSymbol(temporary->arr, 0));

        fprintf(first_scan_output, "%d: OPCODE- %d, src op ref : %d, dst op ref: %d , ARE: %d\n", temp_structure.adress, temp_structure.opcode, temp_structure.src_operand_ref, temp_structure.dst_operand_ref, temp_structure.a_r_e);
    }


    printf("\n");

    return NULL;
}