
#include "assembler.h"




int main(int argc, char** argv) {
    node_t* tmp;
    node_t* head = NULL;
    int i = 1;
    char temp_char = '0';
    char temp_str[LINE_MAX_LEN];
    int j;
    char c;
    int macro_flag = 0;
    int counter = 0;
    int flag;
    int IC, DC;

    char* file_name_holder = malloc(sizeof(char) * BUFFER_MAX);
    char* text_line = malloc(sizeof(char) * BUFFER_MAX);


    /* main loop */
    for (i = 1;i < argc; i++) {
        printf("argc is: %d i is : %d\n", argc, i);


        strcpy(file_name_holder, argv[i]);
        printf("argv is: %s\n", argv[i]);

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


        while (fgets(text_line, LINE_MAX_LEN, file_to_read) != NULL) {

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


            tmp = create_new_node(counter);

            tmp->next = head;

            if (head != NULL)
                head->prev = tmp;
            //macro node

            strcpy(tmp->arr, text_line);
            tmp->value = counter;
            tmp->arr[LINE_MAX_LEN - 1] = END;

            head = tmp;


            counter++;


            fputs(text_line, file_to_write);

        }
        printf("Number of lines in input file is %d\n", counter);
        printf("---------------------------------------------------------------\n");



        rewind(file_to_read);
        rewind(file_to_write);

        fclose(file_to_read);
        fclose(file_to_write);
        fopen("precompiler_output.txt", "r");

        fclose(file_to_write);

        //i++;
        printf("argc is: %d i is : %d\n", argc, i);


        //     struct  Macro* Mtail = NULL;
        //     struct  Macro* Mhead = NULL;
        //     struct  Stable* Stail = NULL;
        //     struct  Stable* Shead = NULL;
        //     struct  Decode* Dtail = NULL;
        //     struct  Decode* Dhead = NULL;
        //     Mhead = (struct Macro*)malloc(sizeof(struct Macro));
        //     Mtail = (struct Macro*)malloc(sizeof(struct Macro));
        //     Mtail = Mhead;
        //     Shead = (struct Stable*)malloc(sizeof(struct Stable));
        //     Stail = (struct Stable*)malloc(sizeof(struct Stable));
        //     Stail = Shead;
        //     Dhead = (struct Decode*)malloc(sizeof(struct Decode));
        //     Dtail = (struct Decode*)malloc(sizeof(struct Decode));
        //     Dtail = Dhead;
        //     flag = PreReadFile(i, argv, Mhead);
        //     if (!flag)
        //     {
        //         PreWriteFile(i, argv, Mtail);
        //         flag = FirstCheck(i, argv, Shead, Dhead, &IC, &DC);
        //         if (!flag)
        //             SecondCheck(i, argv, Stail, Dtail, &IC, &DC);
        //         printentries(i, argv, Stail);
        //         printexternals(i, argv, Stail);
        //     }


        //check for symbol

        //check if "data" "string" or "struct"

        //if label exists put it in the symbol table maked as data with valeo DC, if the symbol allready exists, inform error

        //check for the data type, "code" it
        printlist(head);
    }




    //free(tmp); /*free the memory*/
    return 0;
}
