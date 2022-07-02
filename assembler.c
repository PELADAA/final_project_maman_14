#include <stdio.h>
#include <stdlib.h>


#define LINE_MAX 80 
#define SPACE 32
#define TAB 11
#define NEW_LINE 10
#define END '\0'
#define ASTERISK '*'


struct  node
{
    char arr[LINE_MAX];
    int value;
    struct node* next;
};
typedef struct node node_t;

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
    int counter = 0;



    FILE* file_to_read = fopen(argv[1], "r");
    FILE* file_to_write = fopen("precompiler_output.txt", "w");

    printf("---------------------------------------------------------------\n");
    printf("Input file is %s\n", argv[1]);





    if (file_to_read == NULL || file_to_write == NULL) {
        printf("One of the files does not exist\n");
        return -1;
    }


    while ((c = fgetc(file_to_read)) != EOF) {
        /*if (c == NEW_LINE) {
            c = SPACE;
        }
        if (c <= 0) {
            c = ASTERISK;

            fprintf(stderr, "Warning: Illegal character replaced with * \n");
        }
        */
        counter++;
        fputc(c, file_to_write);

    }
    printf("Number of characters in input file is %d\n", counter);
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
    /*printlist(head);*/

    free(tmp); /*free the memory*/
    return 0;
}
