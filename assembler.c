
#include "assembler.h"





int main(int argc, char** argv) {
    node_t* tmp;
    node_t* head = NULL;
    int i = 1;
    char temp_char = '0';
    char temp_str[LINE_MAX_LEN];
    char macro_name_arr[80][80];

    int j;
    char c;
    int skip = 0;
    int macro_flag = 0;
    int macro_exist = 0;
    int macro_counter;
    int counter = 1;
    int flag;
    int IC, DC;

    char* file_name_holder = malloc(sizeof(char) * BUFFER_MAX);
    char* macro_name_holder = malloc(sizeof(char) * BUFFER_MAX);
    char* text_line = malloc(sizeof(char) * BUFFER_MAX);


    /* main loop */
    for (i = 1;i < argc; i++) {

        macro_counter = 0;


        printf("argc is: %d i is : %d\n", argc, i);

        /* copy raw file name */
        strcpy(file_name_holder, argv[i]);
        printf("argv is: %s\n", argv[i]);
        /* add a suffix */
        strncat(file_name_holder, AS_SUFFIX, SUFFIX_LENGTH);

        printf("file created is: %s\n", file_name_holder);

        /* open relevent files */
        FILE* file_to_read = fopen(file_name_holder, "r");
        FILE* file_to_write = fopen("precompiler_output.txt", "w");
        FILE* macro_table = fopen("macro_table.txt", "w+");
        FILE* macro_index = fopen("macro_index.txt", "w");




        printf("---------------------------------------------------------------\n");

        /* check that files exist */
        if (file_to_read == NULL || file_to_write == NULL) {
            printf("One of the files does not exist\n");
            return -1;
        }

        printf("Input file is %s\n", file_name_holder);

        /* while the line in not null */
        while (fgets(text_line, LINE_MAX_LEN, file_to_read) != NULL) {
            skip = 0;
            if (strstr(text_line, "endmacro") != NULL) {
                printf("%s %d\n", "End macro found in line:", counter);
                fprintf(macro_table, "END OF MACRO");
                macro_flag = 0;
                counter++;
                continue;

            }
            else if (strstr(text_line, "macro") != NULL) {
                printf("%s %d\n", "Macro found in line:", counter);
                macro_flag = 1;
                macro_exist = 1;

                strcpy(macro_name_holder, (clear_spaces(strstr(text_line, "macro"))));
                fprintf(macro_table, "\n[%s]\n", macro_name_holder);

                //printf("\n[%s]\n", (macro_name_holder));

                fprintf(macro_index, "[%s]\n", macro_name_holder);
                strcpy(macro_name_arr[macro_counter], macro_name_holder);
                printf("\nmacro_name_arr [%s]\n", macro_name_arr[macro_counter]);




                macro_counter++;
                counter++;
                continue;
            }

            if (macro_flag == 1) {
                fputs(text_line, macro_table);
                counter++;
                continue;
            }

            if (macro_exist == 1) {

                for (j = macro_counter; j > 0; j--)
                {
                    if (strstr(text_line, macro_name_arr[j - 1])) {
                        printf("macro to replace found: %s in line: %d\n", macro_name_arr[j - 1], counter);
                        rewind(macro_table);

                        while (fgets(text_line, LINE_MAX_LEN, macro_table) != NULL) {
                            printf("checking\n");
                            if (strstr(text_line, macro_name_arr[j - 1]) != NULL) {
                                printf("macro found in table\n");

                                while (fgets(text_line, LINE_MAX_LEN, macro_table) != NULL && strstr(text_line, "END OF MACRO") == NULL) {


                                    printf("running: %s", text_line);
                                    tmp = create_new_node(counter);
                                    tmp->next = head;
                                    if (head != NULL)
                                        head->prev = tmp;

                                    strcpy(tmp->arr, text_line);
                                    tmp->value = counter;
                                    tmp->arr[LINE_MAX_LEN - 1] = END;
                                    head = tmp;
                                    counter++;

                                    fputs(text_line, file_to_write);
                                    skip = 1;
                                }


                            }
                            //fclose(macro_table);
                            //fopen(macro_table, 'w');

                        }

                    }

                    //for (macro counter = 0 ; macro_counter < length(macro_arr); macro_counter++)
                }
            }

            if (skip == 0) {
                /* add node to head */
                tmp = create_new_node(counter);
                tmp->next = head;
                if (head != NULL)
                    head->prev = tmp;

                strcpy(tmp->arr, text_line);
                tmp->value = counter;
                tmp->arr[LINE_MAX_LEN - 1] = END;
                head = tmp;
                counter++;

                fputs(text_line, file_to_write);
            }
        }
        printf("---------------------------------------------------------------\n");

        tmp = create_new_node(counter);
        tmp->next = head;
        if (head != NULL)
            head->prev = tmp;

        strcpy(tmp->arr, "\nEND OF LIST\n");
        tmp->value = counter;
        tmp->arr[LINE_MAX_LEN - 1] = END;
        head = tmp;
        counter++;

        rewind(file_to_read);
        rewind(file_to_write);

        fclose(file_to_read);
        fclose(file_to_write);
        fopen("precompiler_output.txt", "r");

        fclose(file_to_write);
        fclose(macro_table);

        //i++;
        printf("argc is: %d i is : %d\n", argc, i);

        printf("\n");
        printlist(head);
        first_scan(head);
        head = NULL;
        printf("\n");

    }




    //free(tmp); /*free the memory*/
    return 0;
}
