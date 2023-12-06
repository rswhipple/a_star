#include "header.h"
#include "read_line.h"

/* structs */
#ifndef _STRING_ARRAY_
#define _STRING_ARRAY_
typedef struct {
    char** array;
    int size;
} s_array_t;
#endif

#define MAX_TOKENS 9

/* function prototypes */
s_array_t* parse_user_input(int argc, char** argv, legend_t** legend); 
legend_t* parse_first_line(int fd, read_line_t **buf, char** first_line);
s_array_t* read_map(int fd, int num_rows, read_line_t **buf, char* first_line);
s_array_t* create_tokens(char* first_line);
char* copy_numbers_to_string(char* dst, char* src, int* i);
legend_t* create_legend(char** tokens);
bool open_map(int* fd, char* filename);
int get_fd(char* filename);
