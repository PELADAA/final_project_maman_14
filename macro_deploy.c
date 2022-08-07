#include "macro_deploy.h"



void printlist(node_t* head) {
    node_t* temporary = head;
    //node_t* revers_temporary;
    //int i = 0;
    while (temporary->next != NULL) {/* go to the last element*/
        //if (temporary->prev != NULL)

        temporary = temporary->next;

        //printf("%d - \t", temporary->value);
        //printf("%s", temporary->arr);
    }

    //printf("prev is %s\n", temporary->prev->arr);
    while (temporary->prev != NULL) { /* print backwards */
        printf("%d - \t", temporary->value);
        printf("%s\t", temporary->arr);
        temporary = temporary->prev;


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
    result->prev = NULL;

    for (i = 0;i < LINE_MAX_LEN;i++)
        result->arr[i] = SPACE;
    result->arr[LINE_MAX_LEN] = END;
    return result;
}

void insert_after_node(node_t* node_to_insert_after, node_t* newnode) {
    newnode->next = node_to_insert_after->next;
    if (newnode->next != NULL) {
        newnode->next->prev = node_to_insert_after;
    }
    newnode->prev = node_to_insert_after;
    node_to_insert_after = newnode;
}
/*
int check_for_macro(FILE* file_to_read) {

    int macro_flag = 0;
    int macro_exist = 0;
    int counter = 1;
    node_t* tmp;
    FILE* file_to_write = fopen("macro_list.txt", "w");
    char* text_line = malloc(sizeof(char) * BUFFER_MAX);

    printf("start check for macro");

    while (fgets(text_line, LINE_MAX_LEN, file_to_read) != NULL) { //get first line of text


        /*
        if (macro_exist > 0)
        {
            if (strstr(text_line, macro_name[0]) != NULL) {
                printf("macro detected: %s in line %d\n", macro_name[0], counter);

                //rewind(file_to_write);
                while (fgets(text_line, LINE_MAX_LEN, file_to_read) != NULL) {
                    tmp = create_new_node(counter);
                    //printf("test: <%s>\n", text_line);
                    strcpy(tmp->arr, text_line);

                    tmp->value = counter;
                    tmp->arr[LINE_MAX_LEN - 1] = END;
                    //insert_at_head(&head, tmp);
                    counter++;
                }
                //fclose(macro_table);

            }
        }
        */

        /*
        if (strstr(text_line, "endmacro") != NULL) {
            printf("%s %d\n", "End macro found in line:", counter);
            macro_flag = 0;
            printf("---------------------------------------------------------------\n");
        }

        else if (strstr(text_line, "macro") != NULL) {
            //char clean_text[80];
            //char* clean_text_ptr = clean_text;
            //strcpy(clean_text_ptr, text_line);
            //printf("clean_text_ptr <%s> text_line <%s> \n", clear_spaces(text_line), text_line);

            macro_name[0] = clear_spaces(text_line);
            printf("---------------------------------------------------------------\n");
            macro_exist++;
            printf("%s %d name:<%s>\n", "Macro found in line:", counter, macro_name[0]);
            //macro_flag = 1;

            //fprintf(macro_table, "macro in line %d is: %s", counter, (strstr(text_line, "macro")) + 6); //TODO handle spaces
            //save_macro((strstr(text_line, "macro")),)
        }

        if (macro_flag == 1) {
            //fputs(text_line, file_to_read);
            //macro_node = create_new_node(counter);
            //strcpy(macro_node->arr, text_line);
            //macro_node->value = counter;
            //macro_node->arr[LINE_MAX_LEN - 1] = END;
            //insert_at_head(&head, macro_node);//here
        }
        else {
            // tmp = create_new_node(counter);
            // strcpy(tmp->arr, text_line);
            // tmp->value = counter;
            // tmp->arr[LINE_MAX_LEN - 2] = END;
            // //insert_at_head(&node, tmp);//here
        }


        counter++;
        //rewind(file_to_read);
        // fputs(text_line, file_to_read);

    }

}*/
node_t* insert_at_head(node_t** head, node_t* node_to_insert) {
    node_to_insert->next = *head;
    if (*head != NULL) {
        (*head)->prev = node_to_insert;
    }
    *head = node_to_insert;
    node_to_insert->prev = NULL;
    return node_to_insert;
}


node_t* find_node(node_t* head, int value) {
    node_t* tmp = head;
    while (tmp != NULL) {
        if (tmp->value == value) return tmp;
        tmp = tmp->next;
    }
    return NULL;
}

char* clear_spaces(char input_str[]) {

    char* c;
    int i = 0;
    int j = 0;
    *c = SPACE;
    *c = input_str[i];
    while (*c == SPACE) {
        *c = (input_str[i++]);
    }
    i = i + CHARACTERS_IN_WORD_MACRO;
    *c = input_str[i];
    while (*c == SPACE) {
        *c = (input_str[++i]);
    }
    while (isalnum(*c)) {
        temp_str[j] = input_str[i];
        *c = (input_str[++i]);
        j++;
    }
    return temp_str;
}


void addToMtable(struct Macro* head, char name[], char content[]) /*implements a table of macros*/
{
    struct  Macro* temp = NULL;
    temp = (struct Macro*)malloc(sizeof(struct Macro));
    memset(temp->mname, '\0', MAX);
    memset(temp->mcontent, '\0', MAX);
    strcpy(temp->mname, name);
    strcpy(temp->mcontent, content);
    head->next = temp;
}
void printMacroTable(struct Macro* tail) /*Prints the macro table*/
{
    struct  Macro* temp = NULL;
    temp = (struct Macro*)malloc(sizeof(struct Macro));
    temp = tail->next;
    while (temp != NULL)
    {
        printf("\n macro name:  %s \n  content:  %s \n", temp->mname, temp->mcontent);
        temp = temp->next;
    }
}

int IsMacroOrEndm(char line[]) /*Checks whether it is the beginning of a macro or the end of a macro*/
{
    int index = 0, mindex = 0;
    char macro[MAX];
    memset(macro, '\0', MAX);
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        macro[mindex] = line[index];
        mindex++;
        index++;
    }
    if (!strcmp(macro, "macro"))
        return 1;
    if (!strcmp(macro, "endm"))
        return 2;
    return 0;
}
void InsertName(struct Macro* temp, char line[]) /*Enter the macro name in the macros table*/
{
    int index = 0, nindex = 0;
    char name[MAX];
    memset(name, '\0', MAX);
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index]) && line[index] != '\n')
        index++;
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        name[nindex] = line[index];
        nindex++;
        index++;
    }
    strcpy(temp->mname, name);
}
void InsertContent(struct Macro* temp, FILE* fp) /*Inserts the macro contents into the macros table*/
{
    char line[MAX];
    char content[MAX];
    memset(line, '\0', MAX);
    memset(content, '\0', MAX);
    fgets(line, MAX, fp);
    while (IsMacroOrEndm(line) != 2)
    {
        strncat(content, line, MAX);
        fgets(line, MAX, fp);
    }
    strcpy(temp->mcontent, content);
}
int PreReadFile(int i, char* argv[], struct Macro* head) /*Performing the first pass on the file (inserting the macros into the macro table,
                                                        copying the corresponding rows from the table to the file, etc.)*/
{
    char line[MAX];
    FILE* fp;
    memset(line, '\0', MAX);
    fp = fopen(argv[i], "r");
    if (fp == NULL)
    {
        printf("error: cant open the file: %s \n \n", argv[i]);
        return 1;
    }
    while (fgets(line, MAX, fp))
    {
        struct  Macro* temp = NULL;
        temp = (struct Macro*)malloc(sizeof(struct Macro));
        if (IsMacroOrEndm(line) == 1)
        {
            InsertName(temp, line);
            InsertContent(temp, fp);
            head->next = temp;
            head = temp;
        }
    }
    return 0;
}
int IsMacroCall(char line[], FILE* fpw, struct Macro* tail) /*Copy the contents of the corresponding macro to the file from the table, if it is a macro command*/
{
    int index = 0, mindex = 0;
    char Mname[MAX];
    struct  Macro* temp = NULL;
    temp = (struct Macro*)malloc(sizeof(struct Macro));
    temp = tail;
    memset(Mname, '\0', MAX);
    while (isspace(line[index]))
        index++;
    while (!isspace(line[index]) && line[index] != '\n')
    {
        Mname[mindex] = line[index];
        mindex++;
        index++;
    }
    while (temp != NULL)
    {
        if (!strcmp(temp->mname, Mname))
        {
            fprintf(fpw, "%s", temp->mcontent);
            return 1;
        }
        temp = temp->next;
    }
    return 0;
}



void PreWriteFile(int i, char* argv[], struct Macro* tail)
{
    int macroflag = 0;
    FILE* fpw;
    FILE* fpr;
    char line[MAX];
    char fname[MAX];
    char fname2[MAX];
    memset(line, '\0', MAX);
    strcpy(fname, argv[i]);
    strcpy(fname2, argv[i]);
    strncat(fname2, ".am", 3);
    fpr = fopen(fname, "r");
    fpw = fopen(fname2, "w");
    if (fpr == NULL)
        printf("error: cant open the file: %s \n \n", argv[1]);
    while (fgets(line, MAX, fpr))
    {
        if (!macroflag)
        {
            if (!IsMacroCall(line, fpw, tail))
            {
                if (IsMacroOrEndm(line) == 0)
                {
                    fprintf(fpw, "%s", line);
                }
                else
                {
                    macroflag = 1;
                }
            }
        }
        else
        {
            if (IsMacroOrEndm(line) == 2)
                macroflag = 0;
        }
    }
    fclose(fpw);
    fclose(fpr);
}