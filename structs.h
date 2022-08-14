


#include "constants.h"


#ifndef STRUCTS_H
#define STRUCTS_H




/* Structure of an operation (command) word */
typedef struct {
    unsigned int decode : DECODE_SIZE;
    unsigned int destOperand : OPERAND_SIZE;
    unsigned int srcOperand : OPERAND_SIZE;
    unsigned int opcode : OPCODE_SIZE;
    unsigned int group : GROUP_SIZE;
    unsigned int rnd : RND_SIZE;
    unsigned int zeroBit : UNUSED_SIZE;
} cmd_word;

/* Structure of an argument word */
typedef struct {
    unsigned int decode : DECODE_SIZE;
    unsigned int value : VALUE_SIZE;
} arg_word;

/* code structure in decimal numbers */
typedef struct {
    unsigned int adress;
    unsigned int opcode;
    unsigned int src_operand_ref;
    unsigned int dst_operand_ref;
    unsigned int a_r_e;
} int_structure;


typedef struct {
    unsigned int decode : DECODE_SIZE;
    unsigned int destOperand : RED_OPERAND_SIZE;
    unsigned int srcOperand : RED_OPERAND_SIZE;
    unsigned int zeroBit : UNUSED_SIZE;
} reg_word;

typedef union {
    cmd_word cmd;
    reg_word reg;
    arg_word num;
    unsigned int print : 15;
} word;

typedef struct {
    char* label;
    int cmd;
    char** args;
    bool isEffectless;
    bool isEOF;
}input_line;

struct  node
{
    char arr[LINE_MAX_LEN];
    int value;
    struct node* next;
    struct node* prev;
};
typedef struct node node_t;


struct Stable {
    char symbol[MAX];
    int value;
    int baseaddress;
    int offset;
    char attributes[5];
    struct Stable* next;
};

struct Decode {
    char symbol[MAX];
    char opcode[21];
    char funct[5];
    char sregister[5];
    char saddress[3];
    char dregister[5];
    char daddress[3];
    char ssymbol[MAX];
    char dsymbol[MAX];
    char dataorstring[MAX];
    struct Decode* next;
};


#endif