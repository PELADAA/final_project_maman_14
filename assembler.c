
#include "assembler.h"









void printlist(node_t* head) {
    node_t* temporary = head;
    while (temporary != NULL) {
        printf("%d - \t", temporary->value);
        printf("<%s> - \n", temporary->arr);
        temporary = temporary->next;
    }
    printf("\n");
}

node_t* create_new_node(int value) {
    int i = 0;


    node_t* result = malloc(sizeof(node_t));
    node_t result_space = *result;
    node_t* tmp_ptr = result;
    result->value = value;
    result->next = NULL;

    for (i = 0;i < LINE_MAX;i++)
        result->arr[i] = SPACE;
    result->arr[LINE_MAX] = END;



    return tmp_ptr;
}





int main(int argc, char** argv) {
    node_t* tmp;
    node_t* head = NULL;
    int i = 1;
    char temp_char = '0';
    int j;
    char c;
    int macro_flag = 0;
    int counter = 0;

    char* file_name_holder = malloc(sizeof(char) * BUFFER_MAX);
    char* text_line = malloc(sizeof(char) * BUFFER_MAX);
    file_name_holder = argv[1];

    //printf("string after dot is %s\n", strrchr(file_name_holder, DOT));

    strncat(file_name_holder, AS_SUFFIX, SUFFIX_LENGTH);

    printf("file created is: %s\n", file_name_holder);





    FILE* file_to_read = fopen(file_name_holder, "r");
    FILE* file_to_write = fopen("precompiler_output.txt", "w");
    FILE* macro_table = fopen("macro_table.txt", "w");

    printf("---------------------------------------------------------------\n");


    if (file_to_read == NULL || file_to_write == NULL) {
        printf("One of the files does not exist\n");
        return -1;
    }

    printf("Input file is %s\n", file_name_holder);


    //printf(strstr(file_to_read, "macro"));
    //printf(strstr(fgets(,10,file_to_read), "macro")); search macro on every line

    while ((text_line = fgets(text_line, 80, file_to_read)) != NULL) {
        /*if (c == NEW_LINE) {
            c = SPACE;
        }
        if (c <= 0) {
            c = ASTERISK;

            fprintf(stderr, "Warning: Illegal character replaced with * \n");
        }
        */
        if (strstr(text_line, "endmacro") != NULL) {
            printf("%s %d\n", "End macro found in line:", counter);
            macro_flag = 0;


        }
        else if (strstr(text_line, "macro") != NULL) {
            printf("%s %d\n", "Macro found in line:", counter);
            macro_flag = 1;
            fprintf(macro_table, "macro in line %d is: %s", counter, (strstr(text_line, "macro")) + 6); //TODO handle spaces



        }

        if (macro_flag == 1)
            fputs(text_line, macro_table);


        counter++;

        /*if (strstr(text_line, "endmacro") != NULL) {
            printf("End macro found\n");
            macro_flag = 0;


        }
        */
        fputs(text_line, file_to_write);

    }
    printf("Number of lines in input file is %d\n", counter);
    printf("---------------------------------------------------------------\n");



    rewind(file_to_read);
    rewind(file_to_write);

    fclose(file_to_read);
    fclose(file_to_write);
    fopen("precompiler_output.txt", "r");




    while (temp_char != EOF) {

        tmp = create_new_node(i);
        tmp->next = head;

        for (j = 0; j < LINE_MAX; j++) {
            temp_char = fgetc(file_to_write);
            if (temp_char != EOF)
                tmp->arr[j] = temp_char;
        }

        tmp->arr[LINE_MAX] = END;
        head = tmp;
        i++;

    }

    fclose(file_to_write);
    //printlist(head);

    free(tmp); /*free the memory*/
    return 0;
}
