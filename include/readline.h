#include "header.h"

/* structs */
#ifndef _STRUCT_READ_LINE_
#define _STRUCT_READ_LINE_
struct read_line_s {
    char *storage;
    char *leftover;
}; typedef struct read_line_s read_line_t;
#endif

/* macros */
#define READLINE_READ_SIZE 1024

/* function prototypes in readline.c */
char *my_readline(int fd, read_line_t **buf); 
int is_echo(char* string, int bytes);
int find_newline(char* string);
void copy_first_line(read_line_t** buf, char* src, int src_len);
int convert_newline_char(char* string, int bytes);
void flush_readline(read_line_t** buf);
bool init_readline(read_line_t** buf);
bool handle_leftover(read_line_t** buf, int* total_bytes);
int readline_loop(read_line_t** buf, int fd, int* bytes, int* total_bytes);
char* init_string(int len);
