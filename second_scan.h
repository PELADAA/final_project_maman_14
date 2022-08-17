#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "constants.h"
#include "structs.h"
#include "utils.h"


node_t* second_scan(node_t* input_node_head);
node_t* second_scan_with_symbols(node_t* input_node_head, node_t* symbol_node_head);
int isSymbol(char* command, int from);
int isDirective(char* command, int from);
int isOrder(char* command, int from);
int isNumber(char* command, int from);

char* scanner_ptr;



